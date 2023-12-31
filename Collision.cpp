#include "Collision.h"
#include "audio.h"

const Collision::AABB Collision::cameraAABB =
{
    glm::vec3(camera.Position.x - 0.4f, 0, camera.Position.z - 0.4f),
     glm::vec3(camera.Position.x + 0.4f, 1.8f, camera.Position.z + 0.4f)
};


bool Collision::CollisionDetector::checkAABBCollision(const AABB box1, const AABB box2, glm::vec3& collisionNormal, float& penetrationDepth)
{
    // Calculate overlap on each axis
    float overlapX = std::min(box1.max.x, box2.max.x) - std::max(box1.min.x, box2.min.x);
    float overlapY = std::min(box1.max.y, box2.max.y) - std::max(box1.min.y, box2.min.y);
    float overlapZ = std::min(box1.max.z, box2.max.z) - std::max(box1.min.z, box2.min.z);

    // Check for overlap on all axes
    if (overlapX > 0 && overlapY > 0 && overlapZ > 0) {
        // Determine the axis with the smallest overlap (penetration)
        if (overlapX < overlapY && overlapX < overlapZ) {
            collisionNormal = glm::vec3((box1.min.x < box2.min.x) ? -1.0f : 1.0f, 0.0f, 0.0f);
            penetrationDepth = overlapX;
        }
        else if (overlapY < overlapZ) {
            collisionNormal = glm::vec3(0.0f, (box1.min.y < box2.min.y) ? -1.0f : 1.0f, 0.0f);
            penetrationDepth = overlapY;
        }
        else {
            collisionNormal = glm::vec3(0.0f, 0.0f, (box1.min.z < box2.min.z) ? -1.0f : 1.0f);
            penetrationDepth = overlapZ;
        }

        return true; // Collision detected
    }

    return false;
}

bool Collision::CollisionDetector::check(glm::vec3 &normal, float &depth)
{
    AABB box1 = { {-45.0f, 0, -20.1f},{-35.0f,2.0f, -17.0f} };
    AABB box2 =
    {
        glm::vec3(camera.Position.x - 0.4f, 0, camera.Position.z - 0.4f),
         glm::vec3(camera.Position.x + 0.4f, 1.8f, camera.Position.z + 0.4f)
    };

    if (checkAABBCollision(box1, box2, normal, depth))
    {
        return true;
    }
    else
        return  false;
    
}

bool Collision::CollisionDetector::enteredDome()
{
    AABB box1 = { {-45.0f, 0, -17.01f},{-35.0f,2.0f, -17.0f} };
    AABB box2 =
    {
        glm::vec3(camera.Position.x - 0.4f, 0, camera.Position.z - 0.4f),
         glm::vec3(camera.Position.x + 0.4f, 1.8f, camera.Position.z + 0.4f)
    };
    glm::vec3 inormal;
    float idepth;

    if (checkAABBCollision(box1, box2, inormal, idepth))
    {
        return true;
    }
    else
        return  false;
}

bool Collision::CollisionDetector::updateCamPos()
{
    if (camera.fps)
    {
        AABB box1 = { {-85.0f, 0, -90.01f},{25.0f,1.0f, 20.0f} };
        AABB cam =
        {
            glm::vec3(camera.Position.x - 0.6f, 0, camera.Position.z - 0.6f),
             glm::vec3(camera.Position.x + 0.4f, 1.8f, camera.Position.z + 0.4f)
        };
        glm::vec3 inormal;
        float idepth;
        AABB box2 = { {-32.0f, 0, 19.0f} , {-27.0f,1.0f, 20.0f} };
        if (checkAABBCollision(box2, cam, inormal, idepth))
        {
            camera.Position.y = 2.0f;
        }
        else if (checkAABBCollision(box1, cam, inormal, idepth))
        {
            camera.Position.y = 2.5f;
        } else if (camera.Position.z > 55.0f) {
            camera.Position.y = 1.75f;
        }
        else{
            camera.Position.y = 1.5f;
        }
        return true;
    }
    else
        return false;
}

bool Collision::CollisionDetector::checkPlayerCol(glm::vec3& normal, float& depth, bool &obb)
{
    bool col = false;

    AABB box1 = { {-100.0f, 0, -152.1f},{100.0f,2.0f, -150.0f} };
    AABB cam =
    {
        glm::vec3(camera.Position.x - 0.4f, 0, camera.Position.z - 0.4f),
         glm::vec3(camera.Position.x + 0.4f, 1.8f, camera.Position.z + 0.4f)
    };

    if (checkAABBCollision(box1, cam, normal, depth))
    {
        col = true;
    }
    
    AABB box2 = { {+99.0f, 0, -150.1f},{+102.0f,2.0f, 150.0f} };
    if (checkAABBCollision(box2, cam, normal, depth))
    {
        col = true;
    }
    
    AABB box3 = { {-102.0f, 0, -150.0f},{-99.0f,2.0f, 150.0f} };
    if (checkAABBCollision(box3, cam, normal, depth))
    {
        col = true;
    }
    
    AABB box4 = { {-100.0f, 0, +149.1f},{100.0f,2.0f, 152.0f} };
    if (checkAABBCollision(box4, cam, normal, depth))
    {
        col = true;
    }


    AABB box5 = { {-43.0f, 0, -12.1f},{-42.0f,2.0f, -11.0f} };
    if (checkAABBCollision(box5, cam, normal, depth))
    {
        col = true;
    }

    AABB box6 = { {-38.0f, 0, -12.1f},{-37.0f,2.0f, -11.0f} };
    if (checkAABBCollision(box6, cam, normal, depth))
    {
        col = true;
    }
    AABB box7 = { {-37.0f, 0, -17.1f},{-30.0f,2.0f, -16.0f} };
    if (checkAABBCollision(box7, cam, normal, depth))
    {
        col = true;
    }
    AABB box8 = { {-50.0f, 0, -17.1f},{-43.0f,2.0f, -16.0f} };
    if (checkAABBCollision(box8, cam, normal, depth))
    {
        col = true;
    }
    AABB box9 = { {-50.0f, 0, -64.1f},{-30.0f,2.0f, -63.0f} };
    if (checkAABBCollision(box9, cam, normal, depth))
    {
        col = true;
    }

    AABB box10 = { {-64.0f, 0, -50.1f},{-63.0f,2.0f, -30.0f} };
    if (checkAABBCollision(box10, cam, normal, depth))
    {
        col = true;
    }
    AABB box11 = { {-17.0f, 0, -50.1f},{-16.0f,2.0f, -43.0f} };
    if (checkAABBCollision(box11, cam, normal, depth))
    {
        col = true;
    }
    AABB box12 = { {-17.0f, 0, -37.1f},{-16.0f,2.0f, -30.0f} };
    if (checkAABBCollision(box12, cam, normal, depth))
    {
        col = true;
    }
    AABB box13 = { {-12.6f, 0, -32.7f},{-12.0f,2.0f, -32.0f} };
    if (checkAABBCollision(box13, cam, normal, depth))
    {
        col = true;
    }
    AABB box15 = { {-12.6f, 0, -34.4f},{-12.0f,2.0f, -34.0f} };
    if (checkAABBCollision(box15, cam, normal, depth))
    {
        col = true;
    }
    AABB box16 = { {-12.6f, 0, -37.2f},{-12.0f,2.0f, -36.8f} };
    if (checkAABBCollision(box16, cam, normal, depth))
    {
        col = true;
    }
    AABB box17 = { {-12.6f, 0, -43.8f},{-12.0f,2.0f, -43.2f} };
    if (checkAABBCollision(box17, cam, normal, depth))
    {
        col = true;
    }
    AABB box18 = { {-12.6f, 0, -45.8f},{-12.0f,2.0f, -45.2f} };
    if (checkAABBCollision(box18, cam, normal, depth))
    {
        col = true;
    }
    AABB box19 = { {-12.6f, 0, -47.3f},{-12.0f,2.0f, -46.7f} };
    if (checkAABBCollision(box19, cam, normal, depth))
    {
        col = true;
    }
    OBB camOBB(camera.Position, glm::vec3(0.2,1.0f,0.2), glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
    OBB nyaOBB(glm::vec3(-23.0f, 1.0f, -23.0f), glm::vec3(10.0f, 0.5f, 1.0f), glm::angleAxis(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    if (camOBB.checkCollision(nyaOBB))
    {
        obb = true;
        col = true;
    }
    OBB nyaOBB2(glm::vec3(-56.0f, 1.0f, -23.0f), glm::vec3(10.0f, 0.5f, 1.0f), glm::angleAxis(glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    if (camOBB.checkCollision(nyaOBB2))
    {
        obb = true;
        col = true;
    }

    OBB nyaOBB3(glm::vec3(-57.0f, 1.0f, -56.0f), glm::vec3(10.0f, 0.5f, 1.0f), glm::angleAxis(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    if (camOBB.checkCollision(nyaOBB3))
    {
        obb = true;
        col = true;
    }
    OBB nyaOBB4(glm::vec3(-23.0f, 1.0f, -56.0f), glm::vec3(10.0f, 0.5f, 1.0f), glm::angleAxis(glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    if (camOBB.checkCollision(nyaOBB4))
    {
        obb = true;
        col = true;
    }
    
    return col;


}
