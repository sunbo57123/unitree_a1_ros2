代码风格主要参考Google C++ style

### Google C++ Style 规范方法

1. 在线工具
2. IDE ：Clion 
3. IDE ：VSCode 
4.  检查工具：cpplint
5. format工具

### ROS2与Google C++标准的差异

参考： https://docs.ros.org/en/foxy/Contributing/Code-Style-Language-Versions.html

**标准**：Rolling对标的是C++17

**风格**：在Google C++ 风格的基础上作一些修改

**最大行长度为100char**

**头文件应该使用的是.hpp，源文件使用的是.cpp**

**全局变量使用g_开头**

**函数和方法命名**：Google 风格使用的是驼峰命名（CamelCase），但是C++标准库使用的是蛇形命名（snake_case），这种命名方式也行。ROS2核心库现在使用的是蛇形命名，因为一些历史原因或者个人偏好，也没必要一定修改；cpplint不会去检查命名，而且蛇形命名法也更有利于跨语言

具体做法建议：

对于已经存在的项目，推荐已经使用了的风格；对于新的项目，两个都行，更推荐和相关的项目达到风格统一；最终的决定由开发者做出

类的命名默认是使用驼峰命名的。

**访问控制**

Google：

>https://google.github.io/styleguide/cppguide.html#Access_Control
>
>类的数据成员是私有的（private），除非是常量。

在ROS2中，不要求所有的成员变量都是私有的，在必要的时候可以是共有的，应该考虑使用accessor访问，直接访问的话需要是在合理的情景下，而不单单是为了方便。

**类函数对象**

对Lambdas 和 std::function 和 std::bind 没有限制

**boost**

Boost如果不是非常必须的话应该避免使用

**注释**

文档使用 /// 和 /** */ 

笔记和一般注释使用 //

类和函数的注释应该使用 /// 和  /** */ 风格的注释，因为Doxygen and Sphinx in C/C++的建议

描述代码如何工作，或者类和函数中的Notes应该用 // 风格的注释

**指针语法对齐**

:o: `char * c;`

:x: `char* c;` 

:x: `char *c;` 

为了避免这种情况： `char* c, *d, *e;`

**类的权限关键字**

-  `public:`, `private:`, or `protected:` 之前不放1space, it is more consistent for all indentions to be a multiple of 2 所有的锁进都应该是2的倍数
  - rationale: most editors don’t like indentions which are not a multiple of the (soft) tab size
  - Use zero spaces before `public:`, `private:`, or `protected:`, or 2 spaces
  - If you use 2 spaces before, indent other class statements by 2 additional spaces
  - Prefer zero spaces, i.e. `public:`, `private:`, or `protected:` in the same column as the class

**嵌套模版不加空格**

**大括号紧跟  `if`, `else`, `do`, `while`, and `for`, 关键词 ，即使内容只有一行。**

- rationale: less opportunity for visual ambiguity and for complications due to use of macros in the body

  #### 括号处理问题

- 开放括号： `function`, `class`, and `struct` definitions
- 环抱括号： `if`, `else`, `while`, `for`, etc…
  - 除非 `if` 或者 `while`他们的判断条件太长了，必须要回行了，就使用开放括号
- 函数调用不能在一行里解决的，在开放圆括号里面需要换行，第二行使用2个space的缩进，后面的也是使用2space的缩进。
  -  `if`和`while` 条件太长一行搞不定的情况也是这样的

几个例子：

```
// Long condition; open brace
if (
  this && that || both && this && that || both && this && that || both && this && that)
{
  ...
}

// Long function call; wrap at the open parenthesis
call_func(
  foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar,
  foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar);

// Very long function argument; separate it for readability
call_func(
  bang,
  fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo,
  bar, bat);

```

都使用的是2space 缩进

### ROS2的风格检测工具

1. cmake工具

   :one: 在package里加入：

   ```
   <test_depend>ament_lint_auto</test_depend>
   ```

   :two: cmake file 加入

   ```
   # this must happen before the invocation of ament_package()
   if(BUILD_TESTING)
     find_package(ament_lint_auto REQUIRED)
     ament_lint_auto_find_test_dependencies()
   endif()
   ```

   :three: 运行

   ```
   colcon test --event-handlers console_direct+ （可以换成其他命令）
   ```

   默认运行所有的lint检查，不会进行修改，没有lint问题的时候完成CTest。

   

2. 命令行工具

   :one: format 工具

   修改到Google风格

   ```
   clang-format -style=Google -i <filepath>
   ```

   ament工具

   ```
   ament_uncrustify <filepath>
   ```

   :two: 检查工具

   基于cppcheck检查C++风格

   ```
   ament_cppcheck --language=c++ <filepath>
   ```

   基于cpplint检查C++lint 包括copyright等等

   ```
   ament_cpplint <filepath>
   ```

   

