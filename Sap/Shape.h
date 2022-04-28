#ifndef Shape_h
#define Shape_h

namespace Sapper
{

    class Shape
    {
    private:
        float xCenter, yCenter, zCenter;          // ���������� ������
        float xSize, ySize, zSize;                // ������
        float* diffColor, * ambiColor, * specColor; // �������
        int state, num;
        bool flaged = false;
    public:
        Shape(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor);
        virtual ~Shape() { }
        // ������� �������:
        void   setFlaged(bool fl) { this->flaged = fl; }
        bool   getFlaged() { return this->flaged; }
        void   setNum(int num) { this->num = num; }
        int    getNum() { return this->num; }
        void   setState(int state) { this->state = state; }
        int    getState() { return this->state; }
        float  getXCenter() const { return xCenter; }
        float  getYCenter() const { return yCenter; }
        float  getZCenter() const { return zCenter; }
        void   setXCenter(float xCenter) { this->xCenter = xCenter; }
        void   setYCenter(float yCenter) { this->yCenter = yCenter; }
        void   setZCenter(float zCenter) { this->zCenter = zCenter; }
        void   setCoords(float xCenter, float yCenter, float zCenter);
        float  getXSize() const { return xSize; }
        float  getYSize() const { return ySize; }
        float  getZSize() const { return zSize; }
        void   setXSize(float zSize) { this->xSize = xSize; }
        void   setYSize(float zSize) { this->ySize = ySize; }
        void   setZSize(float zSize) { this->zSize = zSize; }
        void   setSize(float xSize, float ySize, float zSize);
        float* getDiffColor() const { return diffColor; }
        float* getAmbiColor() const { return ambiColor; }
        float* getSpecColor() const { return specColor; }
        void   setDiffColor(float* diffColor) { this->diffColor = diffColor; }
        void   setAmbiColor(float* ambiColor) { this->ambiColor = ambiColor; }
        void   setSpecColor(float* specColor) { this->specColor = specColor; }
        void   setColors(float* diffColor, float* ambiColor, float* specColor);
        virtual void draw() = 0; // �� ������� ������� ���� ��������� � �������� ������
    };

}
#endif



