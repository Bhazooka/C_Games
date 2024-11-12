#ifdef BOX_H
#define BOX_H

class Box : public Object {
public:
    float size;
    bool onSide = true;
    
    Box(float x, float y, float size);

    void Update() override;
    void Draw() const;
    void CheckCollisionWithGround();
    void Topple();
    
};

#endif
