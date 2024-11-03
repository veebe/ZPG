#include "ShaderProgramBuilder.h"

ShaderProgramBuilder::ShaderProgramBuilder() : SP(nullptr) {}

ShaderProgramBuilder& ShaderProgramBuilder::CREATE(SHADERTYPES AST) {
	CreateShader(AST);
	SP->AddMaterial(new Material());
	return *this;
}
ShaderProgramBuilder& ShaderProgramBuilder::CREATE(SHADERTYPES AST, Material* AMaterial) {
	CreateShader(AST);
	SP->AddMaterial(AMaterial);
	return *this;
}

void ShaderProgramBuilder::CreateShader(SHADERTYPES AST) {
	switch (AST) {
	case CONSTANT:
		SP = new ShaderProgram(AVertexShader, "ShaderConstant.frag");
		break;
	case LAMBERT:
		SP = new ShaderProgram(AVertexShader, "ShaderLambert.frag");
		break;
	case PHONG:
		SP = new ShaderProgram(AVertexShader, "ShaderPhong.frag");
		break;
	case BLINN:
		SP = new ShaderProgram(AVertexShader, "ShaderBlinn.frag");
		break;
	default:
		break;
	}
}

ShaderProgram* ShaderProgramBuilder::Build() {
	if (SP) {
		return new ShaderProgram(*SP);
	}
	return nullptr;
}
