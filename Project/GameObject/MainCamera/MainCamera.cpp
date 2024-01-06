#include "MainCamera.h"

void MainCamera::Initialize()
{
	viewProjection_.Initialize();
	offset_ = { 0.0f, 2.0f, -16.0f };
}

void MainCamera::Update(const WorldTransform& worldTransform)
{

	
	viewProjection_.translation_ = worldTransform.translate;
	//viewProjection_.rotation_=VectorTransform::Add( Rotate,viewProjection_.rotation_);
	
	//�J������obj����ǂ̈ʂ̋����ɒu����
	Vector3 offset =offset_;
	Vector3 Lerp = VectorTransform::Lerp(worldTransform.translate, viewProjection_.translation_, 1.0f);

	//��]�s��̍���
	Matrix4x4 rotateXMatrix = MatrixTransform::RotateXMatrix(viewProjection_.rotation_.x);
	Matrix4x4 rotateYMatrix = MatrixTransform::RotateYMatrix(viewProjection_.rotation_.y);
	Matrix4x4 rotateZMatrix = MatrixTransform::RotateZMatrix(viewProjection_.rotation_.z);
	Matrix4x4 rotateMatrix = MatrixTransform::Multiply(rotateXMatrix, MatrixTransform::Multiply(rotateYMatrix, rotateZMatrix));
	//�I�t�Z�b�g��J�����̉�]�ɍ��킹�ĉ�]������
	offset = VectorTransform::TransformNormal(offset, rotateMatrix);
	viewProjection_.translation_ = VectorTransform::Add(Lerp, offset);

	viewProjection_.UpdateMatrix();
}
