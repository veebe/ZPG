#include "ShaderProgramBuilder.h"

ShaderProgramBuilder::ShaderProgramBuilder() : SP(nullptr) {}

ShaderProgramBuilder& ShaderProgramBuilder::CREATE(SHADERTYPES AST) {
	CreateShader(AST);
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
	case CONSTANT_TEXTURE:
		SP = new ShaderProgram(AVertexShader, "ShaderConstantTex.frag");
		break;
	case PHONG_TEXTURE:
		SP = new ShaderProgram(AVertexShader, "ShaderPhongTex.frag");
		break;
	case LAMBERT_TEXTURE:
		SP = new ShaderProgram(AVertexShader, "ShaderLambertTex.frag");
		break;
	case BLINN_TEXTURE:
		SP = new ShaderProgram(AVertexShader, "ShaderBlinnTex.frag");
		break;
	case SKYCUBE:
		SP = new ShaderProgram("ShaderSky.vert", "ShaderSky.frag");
		break;
	case SKYCUBE_DYNAMIC:
		SP = new ShaderProgram("ShaderSky.vert", "ShaderSkyDynamic.frag");
		break;
	case STYLIZED:
		SP = new ShaderProgram(AVertexShader, "ShaderStylized.frag");
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
