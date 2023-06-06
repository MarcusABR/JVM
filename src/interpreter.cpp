#include "../include/interpreter.hpp"
#include "../include/class_file.hpp"
#include "../include/method_area.hpp"
#include "../include/types.hpp"
#include "../include/utils.hpp"
#include "../include/frame.hpp"
#include "../include/dump_class_file.hpp"
#include "../include/class_loader.hpp"
#include <iostream>

/**
 * @brief A constant for the object class string 
 */
const string object_class = "java/lang/Object";

// Main method - not used
// const string main_method = "([Ljava/lang/String;)V";

/**
 * @brief Initializes the class methods, starting with main
 * @param class_f the first class file loaded by class loader
 */
void JVMInterpreter::run(class_file *class_f)
{
    //! Loads classes info into method area
    this->load_classes(class_f);

    //! Checks if there is a main method
    method_info main_method = get_main_method(method_a);
    
    frame_t first_frame{&(method_a[object_class].constant_pool)};
    stack<frame_t> stack_f;
    stack_f.push(first_frame);

    //! Executes every frame until there is none left in the stack
    while (!stack_f.empty())
    {
        stack_f.top().execute_frame(main_method, &stack_f);
        cout << "FINISHED FRAME" << endl;
    }
    cout << "END OF RUN" << endl;
}

/**
 * @brief Loads classes into method area 
 * @param class_f the first class file loaded by class loader
 * @return the method area with loaded classes
 */
void JVMInterpreter::load_classes(class_file *class_f)
{
    string class_name = get_name(class_f->constant_pool, class_f->this_class);
    string super_class = get_name(class_f->constant_pool, class_f->super_class);

    /// Searches super class files until it finds java/lang/Object
    /// Each found method is loaded into method area and
    /// mapped as method_name -> method_info
    class_container class_c;
    class_c.constant_pool = class_f->constant_pool;
    
    for (auto method : class_f->methods)
    {
        string method_name = get_utf8_content(*(to_cp_info(class_f->constant_pool[method.name_idx - 1])->_utf8));
        class_c.methods[method_name] = method;
    }

    method_a[super_class] = class_c;
    super_class = get_name(class_f->constant_pool, class_f->super_class);
    
    //! Super class must exist in the examples folder
    if (super_class != object_class)
    {
        string super_class_path = "./examples/" + super_class + ".class";
        if (!exists(super_class_path))
        {
            cout << "Class File \"" << super_class << "\" not in /examples/ - Aborting" << endl;
            exit(1);
        }

        ClassLoader super_class_loader;
        class_f = super_class_loader.load(super_class_path);
        super_class = get_name(class_f->constant_pool, class_f->super_class);
        load_classes(class_f);
    }
}

/**
 * @brief Checks and returns content of the main method if it exits, exit otherwise 
 * @param method_a the loaded method area
 * @return method_info the contents of main method
 */
method_info JVMInterpreter::get_main_method(method_area method_a)
{
    for (auto container : method_a)
        for (auto method : container.second.methods)
            if (method.first == "main")
                return method.second;

    cout << "Main Class not found - Aborting" << endl;
    exit(1);
}