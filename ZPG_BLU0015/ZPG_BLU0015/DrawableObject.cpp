/* Vratislav Blunar - BLU0015 */
#include "DrawableObject.h"

DrawableObject::DrawableObject(TransformationComposite* ATransformation): transformation(ATransformation) {};


void DrawableObject::SetNewTransformation(TransformationComposite* ATC) {
	this->transformation = ATC;
}