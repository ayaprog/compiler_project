#include "codegeneration.hpp"
using namespace std;
// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    cout<< "  .globl Main_main" << endl;
    // WRITEME: Replace with code if necessary
    // Func Prolog -> visit_children -> Func Epilog
    //
    // Function Prologue:
    // 1. Push the current frame pointer value onto the stack
    // 2. Copy the stack pointer value into the frame pointer register
    // 3. Make space on the stack for local variables (decrement stack pointer)
    // 4. Push callee-save register values onto the stack
    //
    // Function Epilogue:
    // 1. Put return value in known register
    // 2. Pop callee-save register values from the stack and restore them
    // 3. Deallocate local variables by moving frame pointer value into stack pointer register
    // 4. Pop caller’s frame pointer value from the stack and put it in the frame pointer register
    // 5. Pop call site’s return address from the stack and jump to it
    // (In x86, the return value register is %eax and point 5 is handled by the ret instruction.)
    node -> visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
    currentClassName = node -> identifier_1 ->name;
    currentClassInfo = (*classTable) [currentClassName];
    
    node -> visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
    currentMethodName = node ->identifier -> name;
    currentMethodInfo = currentClassInfo.methods[currentMethodName];

    cout << "  ##### method (func pro)" << endl;
    cout << "  " << currentClassName << "_" << currentMethodName <<":"<<endl;
    // 1. Push the current frame pointer value onto the stack
    cout << "  push %ebp" << endl;
    
    // 2. Copy the stack pointer value(esp) into the frame pointer register(ebp)
    cout << "  mov %esp, %ebp" << endl;
    
    // 3. Deallocate local variables by moving frame pointer value into stack pointer register
    cout << "  sub $"<< currentMethodInfo.localsSize <<", %esp" <<endl;

    // 4. Push callee-save register values onto the stack

    node -> visit_children(this); 
    // Function Epilogue:
    // 1. Put return value in known register
    // 2. Pop callee-save register values from the stack and restore them
    // 3. Deallocate local variables by moving frame pointer value into stack pointer register
    // 4. Pop caller’s frame pointer value from the stack and put it in the frame pointer register
    // 5. Pop call site’s return address from the stack and jump to it  
    // 
    // cout << "  ##### return states (func epi)" << endl;
    // cout << "  pop %eax" << endl;           // 1. Put return value in known register
    // cout << "  mov %ebp, %esp" <<endl;      // 2. Deallocate local variable space
    // cout << "  pop %ebp" <<endl;            // 3. Restore previous frame pointer value
    // cout << "  ret" <<endl;                 // 4. Pop return address and jump to it
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
    cout << "  ##### return states (func epi)" << endl;
    cout << "  pop %eax" << endl;           // 1. Put return value in known register
    cout << "  mov %ebp, %esp" <<endl;      // 2. Deallocate local variable space
    cout << "  pop %ebp" <<endl;            // 3. Restore previous frame pointer value
    cout << "  ret" <<endl;                 // 4. Pop return address and jump to it
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this);
    cout << "  ##### assignment " << endl;
    cout << "  pop %eax" << endl;
    cout << "  mov %eax,"<< (currentMethodInfo.variables[node->identifier->name]).offset
    << "(%ebp)" << endl;
}

void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this);
    std::cout << "  ##### ADD" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %ebx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary x(eax) - y(ebx)
    node->visit_children(this);
    std::cout << "  ##### Minus" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  sub %ebx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    // x(eax) * y(ebx) -> 
    node->visit_children(this);
    std::cout << "  ##### Times" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %ebx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary numerator x(eax) / y(ebx) -> 
    node->visit_children(this);
    std::cout << "  ##### Divide" << std::endl;
    std::cout << "  pop %ebx" << std::endl; //y denom
    std::cout << "  pop %eax" << std::endl; //x numerator
    std::cout << "  cdq" << std::endl;
    std::cout << "  idiv %ebx" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "pop %eax" <<endl;
    cout << "neg %eax" <<endl;
    cout << "push %eax" <<endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    std::string Variable_Name = node -> identifier -> name;
    cout << "  ##### Variable " << endl; 
    cout << "  push " << currentMethodInfo.variables[Variable_Name].offset <<"(%ebp)" <<endl; 
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "  ##### IntegerLiteral" << endl;
    cout << "  push $" << node->integer->value << endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}