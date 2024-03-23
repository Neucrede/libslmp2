package net.libslmp.melcli4j;

/**
 * Stores model name and type code of the processor of a remote target.
 *
 * @author Neucrede <neucrede@sina.com>
 */
public class TypeName {
    
    private String modelName;
    private int typeCode;

    public TypeName() {
    }

    public TypeName(String modelName, int typeCode) {
        this.modelName = modelName;
        this.typeCode = typeCode;
    }

    public String getModelName() {
        return modelName;
    }

    public void setModelName(String modelName) {
        this.modelName = modelName;
    }

    public int getTypeCode() {
        return typeCode;
    }

    public void setTypeCode(int typeCode) {
        this.typeCode = typeCode;
    }

    @Override
    public String toString() {
        return "TypeName{" + "modelName=" + modelName + ", typeCode=" + typeCode + '}';
    }
    
    
}
