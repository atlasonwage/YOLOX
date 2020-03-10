# By default, the makefile is for debugging.
# The Makefile_Release will have the release build.
CXX=clang++
CXXFLAGS=-Wall -g -fno-omit-frame-pointer -fsanitize=address,leak

.PHONY: clean
clean:
	-rm -f *.o *~ a.out

ASTBlock.o: ASTBlock.cpp ASTBlock.h ASTNode.h GeneralTools.h
ASTBoolExpr.o: ASTBoolExpr.cpp ASTBoolExpr.h ASTBool.h ASTOpParam.h \
  ASTNode.h GeneralTools.h TypeService.h
ASTBoolVar.o: ASTBoolVar.cpp ASTBoolVar.h ASTBool.h ASTOpParam.h \
  ASTNode.h GeneralTools.h TypeService.h ASTVar.h VarReferencer.h
ASTConditional.o: ASTConditional.cpp ASTConditional.h ASTBool.h \
  ASTOpParam.h ASTNode.h GeneralTools.h TypeService.h
ASTLoop.o: ASTLoop.cpp ASTLoop.h ASTBool.h ASTOpParam.h ASTNode.h \
  GeneralTools.h TypeService.h ASTBlock.h ASTConditional.h
ASTOp.o: ASTOp.cpp ASTOp.h ASTVar.h ASTOpParam.h ASTNode.h GeneralTools.h \
  TypeService.h VarReferencer.h
ASTSubCall.o: ASTSubCall.cpp ASTSubCall.h ASTNode.h GeneralTools.h \
  ASTOpParam.h TypeService.h SubroutineManager.h ASTBoolVar.h ASTBool.h \
  ASTVar.h VarReferencer.h
ASTVar.o: ASTVar.cpp ASTVar.h ASTOpParam.h ASTNode.h GeneralTools.h \
  TypeService.h VarReferencer.h
SubroutineManager.o: SubroutineManager.cpp SubroutineManager.h \
  ASTBoolVar.h ASTBool.h ASTOpParam.h ASTNode.h GeneralTools.h \
  TypeService.h ASTVar.h VarReferencer.h
TypeService.o: TypeService.cpp TypeService.h GeneralTools.h
VarReferencer.o: VarReferencer.cpp VarReferencer.h GeneralTools.h