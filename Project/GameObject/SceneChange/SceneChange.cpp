#include "SceneChange.h"

SceneChange* SceneChange::Getinstance()
{
    static SceneChange instance;
    return &instance;
}

void SceneChange::Initialize()
{
    SceneChange::Getinstance()->texHandle_ = TextureManager::LoadTexture("SceneChangeTex.png");
    for (uint32_t spriteCount = 0; spriteCount < SpriteMax; spriteCount++)
    {
        SceneChange::Getinstance()->sprite_[spriteCount] = make_unique<Sprite>();
        SceneChange::Getinstance()->sprite_[spriteCount]->Initialize(new SpriteBoxState,{-64,-64});
        SceneChange::Getinstance()->sprite_[spriteCount]->SetTexHandle(SceneChange::Getinstance()->texHandle_);

        SceneChange::Getinstance()->worldTransform_[spriteCount].Initialize();

    }
    int width = 0;
    int height = 0;

    for (int i = 0; i < SpriteMax; i++)
    {

        SceneChange::Getinstance()->worldTransform_[i].Initialize();
        SceneChange::Getinstance()->worldTransform_[i].scale = { 0,0,0 };
        SceneChange::Getinstance()->worldTransform_[i].translate = { 128.0f * width+64.0f,128.0f * height+64.0f,0 };
        SceneChange::Getinstance()->worldTransform_[i].UpdateMatrix();
        width++;
        if (width % 10 == 0)
        {
            height++;
            width = 0;
        }
    }

 

}

void SceneChange::Update()
{
    int scaleCount = 0;
    for (uint32_t s = 0; s < SpriteMax; s++)
    {
        if (SceneChange::Getinstance()->StartfinishFlag_)
        {
            SceneChange::Getinstance()->worldTransform_[s].scale.x -= 0.05f;
            SceneChange::Getinstance()->worldTransform_[s].scale.y -= 0.05f;
            SceneChange::Getinstance()->worldTransform_[s].scale.z -= 0.05f;

            if (SceneChange::Getinstance()->worldTransform_[s].scale.x <= 0.0f)
            {
                scaleCount ++;
            }
            if (scaleCount>=SpriteMax)
            {
                SceneChange::Getinstance()->EndFlag_ = false;
                SceneChange::Getinstance()->StartFlag_ = false;
                SceneChange::Getinstance()->StartfinishFlag_ = false;
                SceneChange::Getinstance()->EndFinishFlag_ = true;
            }

        }

        if (SceneChange::Getinstance()->StartFlag_&&!SceneChange::Getinstance()->StartfinishFlag_)
        {
            SceneChange::Getinstance()->EndFinishFlag_ = false;
            SceneChange::Getinstance()->worldTransform_[s].scale.x += 0.075f;
            SceneChange::Getinstance()->worldTransform_[s].scale.y += 0.075f;
            SceneChange::Getinstance()->worldTransform_[s].scale.z += 0.075f;

            if (SceneChange::Getinstance()->worldTransform_[s].scale.x>=1.0f)
            {
                scaleCount++;
            }
            if (scaleCount>=SpriteMax)
            {
                SceneChange::Getinstance()->StartFlag_ = false;
                SceneChange::Getinstance()->StartfinishFlag_ = true;
                SceneChange::Getinstance()->EndFlag_ = true;
            }

        }
        SceneChange::Getinstance()->worldTransform_[s].UpdateMatrix();
    }

}

void SceneChange::Draw(ViewProjection view)
{
    for (uint32_t s = 0; s < SpriteMax; s++)
    {
        SceneChange::Getinstance()->sprite_[s]->Draw(SceneChange::Getinstance()->worldTransform_[s],view);
    }
}

void SceneChange::Start()
{
    if (!SceneChange::Getinstance()->StartFlag_&&SceneChange::Getinstance()->EndFinishFlag_)
    {
        SceneChange::Getinstance()->StartFlag_ = true;
    }

}
