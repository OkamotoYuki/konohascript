package compiler.ir;

import konoha.*;
import org.objectweb.asm.*;

import compiler.KMethod;
import compiler.Parser;

public abstract class Inst implements Opcodes {
	
	public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
		throw new GenInstException("TODO: " + this.getClass().getName());
	}
	
	public static class MovInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String from = token[4];
			String to = token[0];
			Type type = parser.toType(token[3]);
			// gen
			gen.movLocal(type, from, to);
		}
	}
	public static class PhiInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// do nothing
		}
	}
	public static class SelectInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String res = token[0];
			Type type = parser.toType(token[3]);
			String cond = token[4];
			String p1 = token[5];
			String p2 = token[6];
			// gen
			Label l1 = new Label();
			Label l2 = new Label();
			gen.loadLocal(cond);
			gen.mv.visitLdcInsn(0);
			gen.jump(IF_ICMPEQ, l1);
			// then
			gen.loadLocal(p1);
			gen.storeLocal(res, type);
			gen.jump(GOTO, l2);
			// else
			gen.mv.visitLabel(l1);
			gen.loadLocal(p2);
			gen.storeLocal(res, type);
			// merge
			gen.mv.visitLabel(l2);
		}
	}
	public static class CastInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String obj = token[4];
			String res = token[0];
			Type type = parser.toType(token[3]);
			// gen
			Type t = gen.getLocalType(obj);
			gen.loadLocal(obj);
			if(t == Type.INT_TYPE) {
				if(type == Type.DOUBLE_TYPE) {
					gen.mv.visitInsn(I2D);
				} else {
					throw new GenInstException("cast error " + t + " to " + type);
				}
			} else if(t == Type.DOUBLE_TYPE) {
				if(type == Type.INT_TYPE) {
					gen.mv.visitInsn(D2I);
				} else {
					throw new GenInstException("cast error " + t + " to " + type);
				}
			} else {
				if(type == Type.INT_TYPE) {
					gen.invokeStatic(K_System.class, "castInt");
				} else if(type == Type.DOUBLE_TYPE) {
					gen.invokeStatic(K_System.class, "castFloat");
				} else if(t.equals(gen.type_String) && type.equals(gen.type_Path)) {
					gen.invokeStatic(K_String.class, "castPath");
				} else if(t.equals(gen.type_String) && type.equals(gen.type_Iterator)) {
					gen.invokeVirtual(K_String.class, "toIterator");
				} else if(t.equals(gen.type_Array) && type.equals(gen.type_Iterator)) {
					gen.invokeVirtual(K_Array.class, "toIterator");
				} else if(t.equals(gen.type_Date) && type.equals(gen.type_String)) {
				} else {
					throw new GenInstException("cast error " + t + " to " + type);
				}
			}
			gen.storeLocal(res, type);
		}
	}
	public static class JmpInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			int n = parser.toBBn(token[3]);
			// gen
			gen.jump(GOTO, n);
		}
	}
	public static class CondInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String cond = token[4];
			int n0 = parser.toBBn(token[5]);
			int n1 = parser.toBBn(token[6]);
			// gen
			gen.loadLocal(cond);
			gen.jump(IFNE, n0);
			gen.jump(GOTO, n1);
		}
	}
	public static class PrintInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			Type type = parser.toType(token[3]);
			int n1 = 0;//Integer.parseInt(token[4]); //TODO
			int n2 = 0;//Integer.parseInt(token[5]);
			String varName = token[6];
			String var = token[7];
			// gen
			if(varName.equals("")) {
				gen.mv.visitInsn(ACONST_NULL);
			} else {
				gen.mv.visitLdcInsn(varName);
			}
			gen.mv.visitLdcInsn(n1);
			gen.mv.visitLdcInsn(n2);
			gen.loadLocal(var);
			gen.box(type);
			gen.invokeStatic(K_System.class, "print");
		}
	}
	public static class TRInst extends Inst {
		public static class BoxInst extends TRInst {
			@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
				// parse
				String res = token[0];
				Type type = parser.toType(token[3]);
				String value = token[4];
				// gen
				gen.loadLocal(value);
				gen.box(gen.getLocalType(value));
				gen.storeLocal(res, type);
			}
		}
		public static class NullInst extends TRInst {
			@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
				// parse
				String res = token[0];
				Type type = parser.toType(token[3]);
				// gen
				if(type.equals(Type.getType("LScript;"))) {
					gen.mv.visitFieldInsn(GETSTATIC,
							"Script", "script0", type.getDescriptor());
				} else {
					gen.mv.visitInsn(ACONST_NULL);
				}
				gen.storeLocal(res, type);
			}
		}
		public static class CwbInst extends TRInst {
			@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
				// parse
				String res = token[0];
				// gen
				gen.invokeStatic(K_OutputStream.class, "getCwb");
				gen.storeLocal(res, Type.getType(konoha.K_OutputStream.class));
			}
		}
		public static class ToStrInst extends TRInst {
			@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
				// parse
				String res = token[0];
				String value = token[4];
				// gen
				gen.loadLocal(value);
				gen.invokeVirtual(K_OutputStream.class, "toStr");
				gen.storeLocal(res, Type.getType(String.class));
			}
		}
		public static class LookupMtdInst extends TRInst {
			
		}
		public static class PropInst extends TRInst {
			@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
				// parse
				String res = token[0];
				Type type = parser.toType(token[3]);
				String value = token[4];
				// gen
				gen.loadLocal(value);
				gen.invokeStatic(K_System.class, "getProp");
				gen.unbox(type);
				gen.storeLocal(res, type);
			}
		}
		public static class VargsInst extends TRInst {
			
		}
		public static class ErrInst extends TRInst {
			
		}
		public static class ChkTypeInst extends TRInst {
			
		}
		public static class DynMtdInst extends TRInst {
			
		}
		public static class PboxInst extends TRInst {

		}
	}
	public static class NewInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String res = token[0];
			String className = parser.toClassName(token[3]);
			// gen
			gen.mv.visitTypeInsn(NEW, className);
			gen.storeLocal(res, Type.getType("L" + className + ";"));
			// call constructor
			gen.loadLocal(res);
			gen.mv.visitMethodInsn(INVOKESPECIAL, className, "<init>", "()V");
		}
	}
	public static class GetIdxInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			Type type = parser.toType(token[3]);
			String arr = token[4];
			String index = token[5];
			String res = token[0];
			// gen
			gen.loadLocal(arr);
			gen.loadLocal(index);
			gen.invokeVirtual(K_Array.class, "get");
			gen.unbox(type);
			gen.storeLocal(res, type);
		}
	}
	public static class SetIdxInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String arr = token[4];
			String value = token[5];
			String index = token[6];
			// gen
			gen.loadLocal(arr);
			gen.loadLocal(index);
			gen.loadLocal(value);
			gen.box(gen.getLocalType(value));
			gen.invokeVirtual(K_Array.class, "set");
		}
	}
	public static class ChkIdxInst extends Inst {
		
	}
	public static class TCheckInst extends Inst {
		
	}
	public static class GetFieldInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			Type type = parser.toType(token[3]);
			String self = token[4];
			int index = Integer.parseInt(token[5]);
			String res = token[0];
			// gen
			gen.loadLocal(self);
			gen.loadField(self, index, type);
			gen.storeLocal(res, type);
		}
	}
	public static class SetFieldInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			Type type = parser.toType(token[3]);
			String self = token[4];
			int index = Integer.parseInt(token[5]);
			String value = token[6];
			// gen
			gen.loadLocal(self);
			gen.loadLocal(value);
			gen.storeField(self, value, index, type);
		}
		
	}
	public static class NextInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			// parse
			String res = token[0];
			Type type = parser.toType(token[3]);
			String itr = token[4];
			int bb1 = parser.toBBn(token[5]);
			int bb2 = parser.toBBn(token[6]);
			// gen
			Label l1 = gen.getLabel(bb1);
			Label l2 = gen.getLabel(bb2);
			gen.loadLocal(itr);
			gen.invokeVirtual(K_Iterator.class, "hasNext");
			gen.jump(IFEQ, l2); // not have next -> bb2
			gen.loadLocal(itr);
			gen.invokeVirtual(K_Iterator.class, "getNext");
			gen.unbox(type);
			gen.storeLocal(res, type);
			gen.jump(GOTO, l1);
		}
	}
	public static class TryInst extends Inst {
		
	}
	public static class CatchInst extends Inst {
		
	}
	public static class ThrowInst extends Inst {
		
	}
	public static class ChkStackInst extends Inst {
		
	}
	public static class AssertInst extends Inst {
		
	}
	public static class LdMtdInst extends Inst {
		
	}
	public static class ReturnInst extends Inst {
		@Override public void asm(KMethod gen, Parser parser, String[] token) throws GenInstException {
			if(token.length >= 4) {
				// parse
				String val = token[3];
				// gen
				Type type = gen.getLocalType(val);
				gen.loadLocal(val);
				gen.mv.visitInsn(type.getOpcode(IRETURN));
			} else {
				gen.mv.visitInsn(RETURN);
			}
		}
	}
	
}
