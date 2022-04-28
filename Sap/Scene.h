#ifndef Scene_h
#define Scene_h

#include "Shape.h"

#include <vector>

namespace Sapper
{

    const int M = 10, N = 10; 

                           
    class Scene
    {
        std::vector<Shape*> shapes; // "гнучкий" масив указівників на елементи гри
        std::vector<Shape*> numbers;
        Shape* boards[10][10];
        int counter;
        int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)
        float angleX, angleY; // поточний кут повороту сцени 
        float mouseX, mouseY; // поточні координати
        float width, height;  // Розміри вікна
        float distZ;          // відстань по осі Z до сцени
        bool finish;          // ознака того, що гру завершено
        
        float xStep, zStep;   // відстань між окремими стрижнями
        int timel;             // поточний час у секуднах
        int fields[M][N];     // масив, у якому відображається розміщення дисків:

        int xFrom, zFrom;     // індекси стрижня, з якого починається пересування
        int xTo, zTo;         // індекси стрижня, яким закінчується пересування
        double x, y, z;
        int m = 10, n = 10, mines = 0, flags = 0, rgh = 0, res;
    public:
        Scene(float xStep, float zStep);
        ~Scene();
        void clearNum(int i,int j);
        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);
    private:
        void Flag(int j, int i);
        void check();
        void initialize();
        void Logic(int x, int z);
        bool findNearest(int x, int z, int& x1, int& z1);
        void resetArr();
        float allocX(int i);
        float allocZ(int i);
    };

}

#endif

