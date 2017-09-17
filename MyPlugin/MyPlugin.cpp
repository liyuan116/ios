#include <iostream>
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
using namespace clang;
using namespace std;
using namespace llvm;
namespace MyPlugin
{
class MyASTVisitor : public
RecursiveASTVisitor<MyASTVisitor>
{
private:
    ASTContext *context;
public:
    void setContext(ASTContext &context){
        this->context = &context;
     }
    //是否是系统类
    bool isFromSystemHeader(Decl *decl) {
        FullSourceLoc fullSourceLoc(decl->getLocation(), this->context->getSourceManager());
        if (fullSourceLoc.isValid() && fullSourceLoc.isInSystemHeader()) {
            return true;
        }
        return false;
    }
    
    std::string _objCLifetimeString(QualType type) {
        switch (type.getObjCLifetime()) {
            case clang::Qualifiers::ObjCLifetime::OCL_None:
            case clang::Qualifiers::ObjCLifetime::OCL_ExplicitNone:
                return "__unsafe_unretained";
            case clang::Qualifiers::ObjCLifetime::OCL_Strong:
                return "__strong";
            case clang::Qualifiers::ObjCLifetime::OCL_Weak:
                return "__weak";
            case clang::Qualifiers::ObjCLifetime::OCL_Autoreleasing:
                return "__autoreleasing";
        }
    }
    
    void translateMethodParameters(ArrayRef<ParmVarDecl*> parameters, bool isOCfunc = true) {
        cout<<"(";
        bool printComma = false;
        if (isOCfunc) {
            cout<<"self,_cmd";
            printComma = true;
        }
        for (ParmVarDecl *decl : parameters) {
            cout<<decl->getNameAsString();
        }
        cout<<")"<<endl;
    }

    
     bool VisitDecl(Decl *decl){
         if(isa<ObjCInterfaceDecl>(decl))
         {
             if(isFromSystemHeader(decl)){
                 return true;
             }
             
             ObjCInterfaceDecl *interDecl = (ObjCInterfaceDecl*)decl;
             
             if (interDecl->getSuperClass()) {
                 string interName = interDecl->getNameAsString();
                 string superClassName = interDecl->getSuperClass()->getNameAsString();
                 cout<<"[LY]ClassName:"<<interName << " superClassName:"<<superClassName<<endl;
                 cout<<"------[LY]Protocol:";
                 for (auto protocolDecl : interDecl->all_referenced_protocols()) {
                     
                     if (protocolDecl) {
                         cout<< ".addProtocol(" <<protocolDecl->getNameAsString()<< ");" <<endl;
                     }
                 }
                 
                 
                 // all ivars (interface and extension)
                 for (ObjCIvarDecl *ivarDecl = interDecl->all_declared_ivar_begin(); ivarDecl; ivarDecl = ivarDecl->getNextIvar()) {
                     ;
                     ivarDecl->getNameAsString();
                     string  lifetimeAttribute;
                     if (ivarDecl->getType()->isObjCRetainableType()) {
                           lifetimeAttribute = _objCLifetimeString(ivarDecl->getType());
                     }
                     cout<<"---------------[LY]Ivar:";
                     if (lifetimeAttribute.length() > 0) {
                         cout<<"addIvar("<<ivarDecl->getNameAsString()<<lifetimeAttribute<<");"<<endl;
                     }else{
                         cout<<"addIvar("<<ivarDecl->getNameAsString()<<");"<<endl;

                     }
                 }
                 
                 for (ObjCMethodDecl *methodDecl : interDecl->methods()) {
                     bool isProtocol = isa<ObjCProtocolDecl>(decl->getDeclContext());
                     string paramContext;
                     if (isProtocol) {
                         paramContext="protocol";
                     }else{
                         paramContext="cls";
                     }
                     cout<<"---------------[LY]MethodFor"<<paramContext;
                     if (methodDecl->isClassMethod()) {
                          cout<<"addClassMethod("<<methodDecl->getSelector().getAsString()<<");";
                         
                     }else{
                         cout<<"addInstanceMethod("<<methodDecl->getSelector().getAsString()<<");";
                     }
                     
                     
                     if (isProtocol) {
                         switch (methodDecl->getImplementationControl()) {
                             case ObjCMethodDecl::None:
                             case ObjCMethodDecl::Required:
                                 cout<<"true"<<endl;
                                 break;
                             case ObjCMethodDecl::Optional:
                                 cout<<"true";
                                 break;
                         }
                     }else{
                         cout<<"function";
                     }

                     translateMethodParameters(methodDecl->parameters());

                 }

             }
             
         }
         
         return true;

    }
};
class MyASTConsumer : public ASTConsumer
{
private:
    MyASTVisitor visitor;
    void HandleTranslationUnit(ASTContext &context){
        visitor.setContext(context);
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
};
class MyASTAction : public PluginASTAction
{
public:
    unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &Compiler,StringRef InFile){
        return unique_ptr<MyASTConsumer>(new MyASTConsumer);
    }
    bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string>& args){
    return true;
    }
};
}
static clang::FrontendPluginRegistry::Add
<MyPlugin::MyASTAction>X("MyPlugin",
"MyPlugin desc");
