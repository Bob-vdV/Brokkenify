In this file all the abbreviations from www.icce.rug.nl are listed (as of December 2022) and which ones are implemented in the code checker.


## Implemented:
### BAK - Blank after keyword

To let keywords stand out, please put a blank after a keyword. So use e.g.: 'for (....)' instead of: 'for(....)'.

Aspect: layout
  
Severity: 1

###C - This looks like C, not C++

Please use C++ rather than C. E.g. use enums instead of preprocessor defines, use static_cast
(expr) instead of (type)(expr), omit the 'typedef' on structs, and avoid preprocessor MACROs. Once they are introduced, use classes rather than loose functions and structs. Also, include C++ headers (cstdlib), not C headers (stdlib.h).

Aspect: style

Severity: 3

### LTL - Line Too Long

Please wrap long lines. We sometimes print your code to check it. If your lines are so long that our LaTeX program wraps them for you, wrapped-around comment may show up as code on the next line, or actual code may be broken of mid-identifier. The result usually wouldn't even compile. Please use multiple lines. (That's not the same as multiple statements.) A line may be too long if, when sending the source file to a printer using A4 paper, the line wraps around to the next line or if the line is truncated. That happens to lines longer than about 78 characters.

Aspect: layout

Severity: 2

### PP - Prefer Prefix 
Please prefer the prefix increment operator (++count) over postfix (count++). The same goes for the decrement operators (--). If their return value is ignored, don't use postfix operators at all.
The prefix operators return by reference, which is cheap. The postfix operators return by value, which means a copy. That copy may be quite expensive, and, if the type has no copy constructor, impossible.
This becomes important when we eventually write our own templates, which may get used with types the author didn't anticipate, long after they were written. Then, a habit of using prefix operators by default becomes an asset.
Ubiquitous code like for (int i = 0; i < end; i++) is not a problem: the compiler is free to optimize i++ into ++i here.

Aspect: robustness 

Severity: 3

### SLV - Single Letter Variable

Please don't use single letter variables. Always use semantically meaningful names. But don't overcompensate by using needlessly long and verbose names.

Aspect: style
        
Severity: 3

### TABS - Do not use Tabs.
Please don't use tabs. Code with tabs for indentation, or worse, with mixed tabs and spaces, is hard to get laid out for printing, which we sometimes do. So always use spaces. Most editors can be told to do that.

Aspect: null
    
Severity: 4

## Won't implement:
### BOUNDS - Array bounds were exceeded, or could have been.

Perhaps you defined an array with too few elements. Perhaps you used an index that exceeded the array's bounds (either below 0 or beyond the end). This may lead to segmentation faults, silent data corruption, or merely wrong computations. Please don't ever do this. Using canonical loops (CANON) helps avoid this mistake. Valgrind may also help, but you may have to write tests to cover them (which is a good idea anyway).

Aspect: integrity

Severity: 5

### AU - Analysis Unit

Please design your solution with the same unit of analysis that is used to state the problem. E.g., a when the problem is stated in terms of words, the program should likely deal with words too, as opposed to single characters or entire files at a time.

Aspect: clarity

Severity: 2

### CTR - Use contractions

Please combine multiple statements into one.

Aspect: style

Severity: 1

Bad example:
cout << *args; //JB: CTR ++args;

Good example:
cout << *args++;

### CW - Compiler Warning

With -Wall, the compiler produced a warning. Please always use '-Wall' when compiling, and polish your code to the point where the compiler issues no warnings.

Aspect: integrity

Severity: 5

Bad example:
for (size_t ix = 1; ix <= argc; ++ix) // JB: CW

### COCO - Const-Correctness

We found a variable or parameter that could be (more) const, but isn't. In C++, please always make const whatever can be const.

Aspect: robustness

Severity: 2

### SEGF - SEGFAULT (Segmentation Fault)

Your program could cause a segmentation fault at this point. A segmentation fault is the kernel stopping your program because it has done something it must not do (usually: tried to access memory it doesn't own). Segmentation faults are often the result of some other mistake, like out-of-bounds indexes, failure to initialize variables, or neglecting to check for null pointers. Please always prevent segmentation faults.

Aspect: integrity

Severity: 5

## Not implemented (yet):

### ABC - Align Break and Case

Please put break statements at the same indentation level as the case labels they end. Indent statements in between. If a case ends in a continue, return, or throw, put those at the indentation level of the matching case. Don't forget to explicitly end a default entry.

Aspect: layout

Severity: 1

Bad example:
switch (ch) { case '\n': flags |= SEPARATOR; break; case 'a': ... }

Good example:
switch (ch) { case '\n': flags |= SEPARATOR; break; // same indentation as 'case' above. case 'a': if (flags > SEPARATOR) return 0; ... }

### ANS - Use an Anonymous NameSpace

An anonymous namespace is a good place for things you factored out of a function, but that are only used in this file. A function at global scope in a source file gets external linkage, so it can be found during linking. The content of an AN OTOH gets internal linkage, so only the current translation unit 'sees' it. If the factored-out expression is large, or if there are many, please consider using two ANs: one before the global-scope function, where you only declare/define whatever necessary, and one after it, where the rest of the definitions go. The compiler will then combine both ANs for you. This way the global-scope function can remain reasonably high up in the file.

Aspect: structure

Severity: 2

Good example:
\#include <stdexcept> namespace { bool valid_as_bit(char ch) { return ch =='0' || ch == '1'; } char const e_msg_invalid_bit[] = "Invalid input: bits can only have values '1' or '0'."; } // Convert e.g. '1101' to 13. unsigned int base2_to_uint(char const *bits) { int retval = 0; while (*bits != '\0') { if (not valid_as_bit(*bits)) throw(std::runtime_error(e_msg_invalid_bit)); retval <<= 1; retval |= *bits++ == '1' ? 1u : 0u; } return retval; }

### BABO - Blanks Around Binary Operators

Please put blanks around binary operators. Write: 'a + b' rather than: 'a+b'. A less dense layout is a bit easier on the eye. Exceptions are comma (','), scope resolution ('::) and member access ('.' and '->') operators. Threat the comma as you would in plain text: put a space after, but not before. Treat scope resolution and member access operators as you would a hyphen in plain text: with no spaces on either side.

Aspect: layout

Severity: 2


### BD - Bad Design

The design of your software contains serious flaws, like including your class header in your internal header after including other headers. This might render the class header uncompilable when users merely include your class's header file.

Aspect: consistency

Severity: 3

### BH - Bad Header(s)

Please include all necessary headers, and no more. Most often, 'BH' indicates you included too bulky a header. It's a waste of compile time to e.g. include 'iostream' (which defines streams) when including 'iosfwd' (which merely declares streams) would do.
Another reason for 'BH' is if you forget a header you do need. E.g. the 'algorithm' header happens to include the 'vector' header, but there is no guarantee it will continue to do so in the future. So if your program includes 'algorithm' and manipulates std::vectors, it should include 'vector' too.
Yet another 'BH' case is when you include an internal header in a public header.

Aspect: efficiency

Severity: 3

Bad example:
int main(int argc, char **argv) { // Quick check for '-h' option. if (argv[1][1] == 'h') // JB: BOUNDS if argc == 1 usage(); }

### BS - Bad Style

A marked departure from established conventions, like a program terminating with exit value 0 when its normal/intended behavior could not be performed, or RBA where a proper return would've worked, or needlessly using static storage duration on a local variable, or ... There are many possibilities. Please handle the case more conventionally.

Aspect: consistency

Severity: 3

### CANON - Use canonical for-statements

Off-by one errors are common in for-loops. The fewer variations of loop control, the better. So please stick to a few common loop control patterns if at all possible. If 'iter' is the loop control variable and 'end' its end-value, the loop control of an incrementing canonical for statement looks like: for (initialization; iter != end; ++iter). For a decrementing canonical for statement it looks like: for (initialization; iter--; ).' FixMe: link to canonical loops.

Aspect: consistency

Severity: 3

Bad example:
for (size_t ix = 1; ix <= argc; ++ix) // JB: CANON, CW cout << argv[ix - 1] << ' ';

Good example:
for (size_t ix = 1; ix != static_cast<size_t>(argc); ++ix) cout << argv[ix] << ' ';

### CC - Cluttering Comment

Please keep comments short to avoid drowning the code. Longer comments can go at the start or (preferably) end of a file, so as not to disrupt reading of the code. Comment should inform the reader about the purpose of the code, not so much about how it works (NSC). In particular, comment should not re-state what the code already expresses. 'CC' sometimes also stands for: "Confusing Comment', when the comment is actually a lie, as happens occasionally when the author updates the code but not the comment.

Aspect: clarity

Severity: 2

### DECO - Demo Code

When providing demo code (in text, outside source files) please make sure that you still adhere to the style conventions. So properly layout your code, no variables/functions that start with capitals, no SLVs, etc. etc. Make sure that your demo code looks as nice as code you pass through the compiler.

Aspect: style

Severity: 3

### DELEG - Use Constructor Delegation

Please consider constructor delegation, where one constructor calls another. It can often avoid duplicate code.

Aspect: efficiency

Severity: 2

### DM - Improper Data Member

Please refer to the hints&tips file for an overview of how to define return/parameter types. Apply those considerations also to the definition of data members. In particular, prevent unnecessary copying of objects passed to constructors if your class only uses the passed object's members.

Aspect: efficiency

Severity: 3

Bad example:
class Proxy { string d_str; // Should've been string & or maybe string const & ... public: Proxy(string const &str); };

### DORD - Department of Redundancy Department

Please don't redo things already done or implied. (FACTOR is when you do the same thing twice. DRY is when you have multiple solutions for one problem. DORD is when you do something (again) that you didn't have to.)

Aspect: clarity

Severity: 2

Bad example:
int main() { unsigned int age = 0; string name = ""; //JB: DORD: default constructor suffices. cin >> name >> age; if (name.empty()) { cerr << "Can't work with empty name.\n"; return ERR_NAME_EMPTY; } else if (not name.empty() && age < 18) // JB: DORD: first part will never match. { cerr << "You are a minor.\n"; return ERR_MINOR; } cout << "Welcome, " << name << '\n'; return 0; // JB: DORD, C }

### DRY - Don't Repeat Yourself

Please use only one representation to deal with each kind of situation. E.g. when allocating memory for a class, don't use new[] in some cases and and placement new in others. This mistake seems to happen in particular when two partial solutions are merged into one.

Aspect: structure

Severity: 3

### FACTOR - Factorize your code

Instead of copying (major parts of) one function in another, please define the common part in a function of its own, which you can use to implement the original functions. Updating copy-pasted code is a cause of bugs when one copy gets fixed but others don't. Note that the extra function call is not a problem, because the compiler will inline the function if it thinks the call is too slow. We also write FACTOR when code is not actually copied, but some functionality factored out and reused to reduce the amount of code.

Aspect: structure

Severity: 2

Bad example:
int main(int argc, char **argv) { extern char **environ; char **end = environ; while (*end != 0) ++end; cout << (end - environ) << " envvars\n"; end = argv; while (*end != 0) //JB: FACTOR ++end; //JB: FACTOR cout << (end - argv) << " args\n"; }

Good example:
size_t ntbs_count(char const * const *start); int main(int argc, char **argv) { extern char **environ; cout << ntbs_count(environ) << " envvars\n"; cout << ntbs_count(argv) << " args\n"; } size_t ntbs_count(char const * const *start) { char const * const *end = start; while (*end != nullptr) ++end; return end - start; }

### FLOW - Bad flow control

Please use flow control constructions appropriately. E.g. 'else' after a return is usually superfluous. We prefer (more efficient and more readable) switch statements over if-else ladders. Ternary operators whose return value is ignored should've been if-statements. If-statements where the same variable is assigned in both branches should've been ternary operators.

Aspect: style

Severity: 2

Bad example:
int main(int argc, char **argv) { bool has_args = false; if (argc > 1) has_args = true; // JB: CTR/FLOW: use ternary //JB: FLOW: ternary used as if-stmt. (return value ignored) has_args ? cout << "args given" : cout << "no args"; //JB: FLOW: Possibly return E_NO_ARGS here, or if not, //JB: continue without needing extra indentation. if (has_args) { Op operator; if (argv[1][0] == 'a') operator = ADD; // JB: FLOW: use switch, not if-else ladder. else if (argv[1][0] == 'm') operator = MULTIPLY; else if (argv[1][0] == 's') operator = SUBTRACT; else if (argv[1][0] == 'd') operator = DIVIDE; size_t ix = 2; // JB: FLOW: while-loop on known number of iterations. while (ix != argc) process(argv[ix]); return 0; } else //JB: SF else after return. return E_NO_ARGS; }

### FT - Finishing Touch

The code is not bad, but please make one more pass over it. We think it could be made nicer. You may have e.g. left in commented-out debug statements, forgotten to move some header includes over to the internal header. Maybe the vertical layout or the grouping of statements has become illogical...

Aspect: style

Severity: 3

### GUARDS - Header needs include guards

Please always put include guards on your public header files. Internal headers do not need include guards, but if they contain definitions, it doesn't hurt either.

Aspect: integrity

Severity: 5

### HAT - Hints and Tips

Please consult the hints.shtml file. The hints are sorted by lecture, so check the hints for the current and previous lectures.

Aspect: style

Severity: 3

### IBI - Inline Below Interfaces

Please define inline members below the class interface. See the Hints and Tips about this topic for details.

Aspect: layout

Severity: 3

### ICI - In-Class Implementation

Please separate the class' implementation from the interface. The interface should show what the class can do, not how it does it. So class members should never be defined inside the class interface, only declared. For their definitions, use separate source files, or (for very small member definitions about which you're *very* sure:) define inline implementations below the interface (public members) or if possible in the internal header (private members)).

Aspect: layout

Severity: 5

Bad example:
class MyClass{ int d_nr; public: number(int nr) { //JB: ICI d_nr = nr; } ... };

Good example:
class MyClass{ int d_nr; public: number(int nr); ... }; MyClass::number(int nr) { d_nr = nr; }

### IF - Include First

In the internal header of a class, include the class' header file first, before including other things. This ensures that the compiler will see process myclass.h without before any other includes, which serves as a check that myclass.h itself does indeed include all it needs.

Aspect: robustness

Severity: 2

Bad example:
// This is the file myclass.ih #include <iosfwd> #include "myclass.h" //JB: IF.

Good example:
// This is the file myclass.ih #include "myclass.h" //JB: .h missing iosfwd? Detected here! #include <iosfwd>

### IH - Internal Header

Please use an internal header. The source files containing the (member) functions the class header offers can then all include this internal header, and nothing else. This reduces the number of #include statements you have to write, and when using precompiled headers, it also reduces build time.

Aspect: efficiency

Severity: 4

### INCONS - Inconsistency

Please act the same in similar cases. Usually we'll encircle the cases you treated differently.

Aspect: consistency

Severity: 2

### IRE - Inefficient Repeated Evaluations

If an expression won't change its value, don't evaluate it time and again. Define a (const) variable before starting the iterations, and use that instead.

Aspect: efficiency

Severity: 2

### JAVA - Java new

The program is allocating on the heap what can be done using a local variable. Memory allocation takes some time, so don't do it without cause. Beside this efficiency issue, there is also a structural one: C++ requires that new and delete be balanced by the programmer. This balance is easily lost in later edits, so it's better to encapsulate allocation, rather than do it locally in a function.

Aspect: efficiency

Severity: 3

### KLUDGE - The implemenation is a kludge

We all do quick-and-dirty once in a while. But this is too dirty. Please straighten it out. Mild kludginess is often given away by a sudden statement that fills in some gap at the end of your code.

Aspect: clarity

Severity: 3

### LEAK - The program may leak a resource

If your program acquires resources during its run time, please ensure that it releases those resources before terminating. Memory leaks are the most common. Valgrind can be used to spot them. Other resources (processes, temporary files) can be leaked too. Encapsulating allocations inside classes is a good strategy to avoid leaks.

Aspect: integrity

Severity: 5

### LOC - Localize Variables

Please define variables in such a way that their visibility and lifetime is as limited as possible. This reduces the number of places where variables can influence flow, which makes the code easier to read. In particular, don't define all the variables at the start of the block as you would in C. Do initialize them at their definition (RAII).

Aspect: robustness

Severity: 3

### L - Layout

Generic layout violation. Usually inconsistent indentation or questionable layout. Occasionally you see perfect layout but to us it looks messed up. That's likely a case of TABS.

Aspect: layout

Severity: 1

### MF1F - Multiple Functions, 1 File

Please don't define multiple functions in one source file. Compilation turns the file into an object module. Object modules are brought together in a library. When a program is linked against the library, modules (not mere functions) are linked into the program. So if the program needs one function from the module, it gets the entire module. That's our reason to give each function a module (and therefore a source file) of its own. The exception is when your function needs helper functions no one else needs. Those can be put in an anonymous namespace in the same file. If you do that, declare the helper functions before the most important function, but define them after it.

Aspect: efficiency

Severity: 5

### MI - Use Member Initializers

Please use initialization for data members. By the start (opening curly) of the constructor body, all data members have been default-initialized. If the data member is an object, please specify a member-initializer for it, that will then be used instead of the default initializer. If the ddata member is of a built-in type, please still specify a member initializer for it, to gain our trust that you know how to. Please do note that constructor delegation is sometimes even more efficient than member initializers.

Aspect: robustness

Severity: 3

### MLR - Multiple Levels of Responsibility

A function should do one thing, and delegate details/subtasks to helper functions. E.g. a function that outputs a list of strings should not also deal with individual chars. Please factor out part of the work into one or more helper functions.

Aspect: structure

Severity: 3

### MR - Multiple Responsibilities

A function should do one thing. A function that does multiple things can only be reused when all those things have to be done again, in the same order. Even if a function can do two things at the same time (e.g. open files and count them), it is often a good idea to split the functionality into single-purpose functions. Please do so.

Aspect: structure

Severity: 3

### MS1L - Multiple statements on one Line

Please don't do e.g. 'if (cond) var = value;', or 'int value = 3, count = 0;' Each statement should be written on a line of its own, and nested statements should be indented. Nested compound statements use the same indentation as their main statement, but the statements they contain are indented.

Aspect: style

Severity: 5

### NAE - Not According to Exercise

The program deviates on essential points from the requirements stated in the exercise. Please fix.

Aspect: correctness

Severity: 5

### NAMING - Name your identifiers for their purposes.

The identifiers that name your types, functions, variables etc. should help document what the program does. Please give them reasonably brief, clear names.

Aspect: clarity

Severity: 2

Bad example:
char const *a = s; // JB: NAMING (2x) while (*a != '\0') // JB: NSC ++a; size_t TheValueThatWeComputeAsLength = a - s; // JB: NAMING return TheValueThatWeComputeAsLength; // JB: CTR

Good example:
char const *end = begin; while (*end != '\0') //JB: Better, but still NSC. ++end; return end - begin;

### NC - Not Covered

Please don't use features of C++ we haven't covered yet, especially if the exercise doesn't require them. Try to restrict yourself to the elements of the language we have covered so far. If you think the solution is suboptimal without a feature you would've liked to use, do feel free to mention that in a comment.

Aspect: educational

Severity: 5

### NEST - Too many nesting levels

Please don't nest loops and conditionals too deeply. It makes seeing what's going on too hard. Consider what you would do when explaining the function to somebody else. Chances are that you wouldn't come up with a complex series of conditions and repititions all closely interconnected. Rather, you''d use summarizing statements for conceptually distinct sections. Follow that process too when writing software: use a conceptual analysis and define support functions to implement the parts emerging from your analysis. Usually, three levels is already a bit much.

Aspect: structure

Severity: 3

### NFT - Needs Final Touch

Please take a moment to tidy up your solution. If we comment NFT, likely there are no big mistakes. It just doesn't look inviting. Perhaps the layout is ugly. Perhaps the functions cut the code into unelegant pieces. Take another look, and make it nicer, please.

Aspect: layout

Severity: 3

### NMN - No Magic Numbers

Writing a 3 is fine when it means: 3. When it means: 'the exit code we return when an extended input/output extended error occurs', please give it a symbolic name, like: 'EIEIO'. This is convenient in case the program later on needs a value of 4 for that exit code. You don''t want to have to sif through all the occurrences of the digit '3's in the source code and for each one decide whether it needs to be changed or not. Just changing: EIEIO = 4, // was 3 is much more convenient.

Aspect: robustness

Severity: 3

Good example:
enum { ESUCCESS = 0, EUNKNOWN = 1, EIO = 2, // simple IO error EIEIO = 3, // extended IO error }; bool all_divisible_by_3(std::istream &ins) { int number; while (true) { in >> number; if (ins.eof()) return true; if (not ins.good()) exit(ins.bad() ? EIEIO : EIO); if (number % 3 != 0) return false; } return true; }

### NSC - Needs Semantic Comment

Statements should be provided with eoln-type semantic comment, briefly explaining why the statement is used. Briefly means 1, at most 2 lines. Semantic comment should normally start near column 40. The different indentation serves to prevent it from cluttering the code. If a statement is too long to allow semantic comment put the comment above the statement. Better yet than comments are statements so clear they don't need any.

Aspect: robustness

Severity: 3

### OOM - Out Of Memory

Your program might fill the computer's entire RAM, causing it to become unresponsive. This might happen e.g. when you read a file into memory and the file is large. If having the entire file in memory is necessary, that's just a limit the hardware poses to the problem size. But if you could've read the file a line or a character at a time, it's a mistake.

Aspect: integrity

Severity: 4

### PAR - Improper parameter type

Please refer to the HATs for an overview of how to define return/parameter types. //FixMe: Link

Aspect: structure

Severity: 3

### PASCAL - Pascal-style loop

The program uses the same statement both before and in a loop, in the way a Pascal programmer would write it. In C++, please use a perpetual loop to achieve the same result without repeating an expression.

Aspect: robustness

Severity: 3

Bad example:
cin >> word; //JB: PASCAL while (cin && word != "quit") { cout << '"' << word << "\" "; cin >> word; }

Good example:
while (true) { cin >> word; if (!cin || word == "quit") break; cout << '"' << word << "\" "; }

### Perl - SF curlies around a single statement

Please don't turn a single statement into a compound statement just because it forms a branch of a conditional statement or the body of a loop. If it's a single statement, the curlies are superfluous. In the Perl programming language they are not, hence the abbreviation.

Aspect: style

Severity: 1

Bad example:
if (valid(ch)) { // JB: Perl ++count; }

Good example:
if (valid(ch)) ++count;

### PH - Missing or incomplete project header

Like internal class headers, please define a project header (e.g. main.ih) containing all requirements (include directives, namespace use specifications, project function and maybe global variable declarations) that are needed to compile all sources at the main project directory. Note that this too is an internal header, so include guards are not necessary.

Aspect: efficiency

Severity: 3

### PO - Premature Optimization

Don't stray from the problem at hand in an attempt to do something `smart'. Follow the description of the algorithm as closely as possible in the implementation. Optimize only once you know where the bottlenecks are.

Aspect: robustness

Severity: 3

### PWPF - Penny-Wise, Pound-Foolish

Don't think for the compiler or architecture. Express your ideas as clearly as possible in code. The compiler will work on efficiency. If you try to think for the compiler, you often end up losing more than you save. E.g., using 'short' instead of 'int' where that conceptually isn't required should be avoided because, although you may save a byte or two in data, the compiler is required to throw in additional code to force the values resulting from computations into the short's size. This additional code exceeds the bytes you gained in storage, and needlessly slows down your program.

Aspect: robustness

Severity: 3

### Q - Questionable

Please reconsider your solution. Although the code may be acceptable and even clever, it is also possible that you tried to sidestep the problem. We can't tell. Please ask yourself if your code really implements your intentions and why you wrote it this way. When in doubt, please state your intentions in comment or in a text file. You may have found one of those solutions that we accept if you thought it through, but reject if you just stumbled into it.

Aspect: educational

Severity: 5

### RAII - Resource Aquisition Is Initialization

Whenever you acquire some resource (i.e., define a variable or object) please initialize it properly a.s.a.p. An exception could be to not initialize a built-in value if in the next statement you are going to give it a value from input. But even then, initializing it before I/O is a safe practice. You can always remove the initialization later on during optimization if it turns out that it's sitting in the hot path and it requires speedup and the compiler doesn't do it for you.

Aspect: robustness

Severity: 5

### RBA - Return By Argument

Please put `output' parameters before `input' parameters, and define `output' parameters as pointers, to make clear by the way the function is called that their values are changed intentionally.

Aspect: style

Severity: 1

### RBFL - Range Based For Loop

Please consider a range based for-loop. We think it would be the natural syntactic form to use.

Aspect: clarity

Severity: 1

### RET - Improper return type

Please refer to the HATs for an overview of how to define return/parameter types.

Aspect: structure

Severity: 3

### RTFM - Read The Fantastic Manual

The notorious RTFM advice. To us it looked like you did not read these abbreviations, the HAT, the Annotations, or perhaps none of them at all. We politely request that you do. We may be wrong though. If you think we are, please feel free to contact us.

Aspect: educational

Severity: 5

### SEM - Semantics

Don't let the implementation of your functions diverge too much from what you would tell somebody when explaining what it is they do. When designing functions follow their semantics, and if elements diverge too much from that define helper functions.

Aspect: clarity

Severity: 3

### SF - Superfluous

We think you wrote something that could be left out. Examples are curlies, parentheses, assignments of default values right after initialization, elses after returns, entirely unused variables. Please make your code shorter by removing the superfluous part.

Aspect: robustness

Severity: 3

### TC - Too complex

Please simplify your solution. It may work. It may even be coded cleanly. But we think simpler alternatives exist. We also write: 'TC' if we simply don't understand your code.

Aspect: clarity

Severity: 5

### TME - Too Many Errors

The exercise contains too many errors to make it worthwile to continue rating it. Please reconsider your approach, repair the errors and comparable errors below this point and, if possible, resubmit.

Aspect: clarity

Severity: 5

### TV - Too Verbose

Your answer is too verbose or convoluted to be rated. Submit a (much) shorter answer, showing only the essence. Maybe use a small table summarizing your answer?

Aspect: educational

Severity: 5

### TYPE - Bad type of variable

The type of a variable should help convey its purpose. E.g. a count never becomes negative, so please don't use a signed int for it.

Aspect: clarity

Severity: 3

### UM - Use a/another member function

We think there already is a member function that does what you want. Please use it. When using a class, it pays off to know the available members, so you don't roll your own or use one member function where a more fitting one exists.

Aspect: structure

Severity: 3

### VI - Verbose Identifier

Don't use overly verbose namens, like computeTheLengthOfAStringThatIsPassedAsArgument. Try to capture the essence of the identifier's meaning in a short name. E.g., use 'length' instead. The function's argument already suggests that its length will be computed.

Aspect: clarity

Severity: 3

### WC - Won't Compile

All your sources should compile using a recent GNU g++. We think this one doesn't.

Aspect: integrity

Severity: 5

### WHEEL - Don't reinvent the wheel

There exists a function that performs the task you're implementing. Please use it.

Aspect: robustness

Severity: 3

### WILD - Wild pointer

Dereferencing WILD pointers may cause segfaults, and usually will. When using pointers please ALWAYS make sure they have well-defined values: either 0 (nullptr), or pointing to existing memory owned by the program.

Aspect: integrity

Severity: 5

### WIM - What Is Modified?

You're defining or declaring a member function, but it isn't clear what data members are modified by the function. If a member function does not modify data members of its object, it should have the `const' attribute.

Aspect: robustness

Severity: 1
