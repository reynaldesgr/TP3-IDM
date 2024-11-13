#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/objet_graphique.h"

int main()
{
    srand(time(NULL));

    /***********************************
     *          ENCAPSULATION          *
    ************************************/

    // ObjetGraphique's instance with default values.
    ObjetGraphique* objDefault = createDefaultObjetGraphique();

    // Test 1: Default Constructor
    printf("\n [Test 1] - Constructor (default) \n");
    printf("  Object: x = %d, y = %d\n", objDefault->myClass->getX(objDefault), objDefault->myClass->getY(objDefault));

    // ObjetGraphique's instances.
    ObjetGraphique*  obj1  = createObjetGraphique(rand() % 100, rand() % 100);
    ObjetGraphique*  obj2  = createObjetGraphique(rand() % 100, rand() % 100);
    ObjetGraphique*  obj3  = createObjetGraphique(rand() % 100, rand() % 100);

    // Check if ObjetGraphique's objects has been correctly created.
    if (obj1 == NULL || obj2 == NULL || obj3 == NULL)
    {
        printf("     [!] Objects not correctly created.");
        return 1;
    }

    // Test 2: Ad-hoc constructor
    printf("\n [Tests 2] - Constructor (ad hoc) \n");
    printf("  Object 1 (obj1) : x = %d, y = %d\n", obj1->myClass->getX(obj1), obj1->myClass->getY(obj1));
    printf("  Object 2 (obj2) : x = %d, y = %d\n", obj2->myClass->getX(obj2), obj2->myClass->getY(obj2));
    printf("  Object 3 (obj3) : x = %d, y = %d\n", obj3->myClass->getX(obj3), obj3->myClass->getY(obj3)); 

    // Test 3: Setters & getters
    obj1->myClass->setX(obj1, 50);
    obj1->myClass->setY(obj1, 75);
    printf("\n[Test 3] - Setters & getters\n");
    printf("  (After calling the setter) Object 1: x = %d, y = %d (Expected: x = 50, y = 75)\n",
           obj1->myClass->getX(obj1), obj1->myClass->getY(obj1));

    // Test 4: Instance count test
    int init = obj1->myClass->GetNbObjetGraphique(obj1->myClass);
    printf("\n[Test 4] - Instance count\n");
    printf("  Initial object count: %d\n", init);

    // Store a reference to class before freeing
    MetaObjetGraphique* classReference = obj1->myClass;

    // Free ObjetGraphique's objects
    freeObjetGraphique(objDefault);
    freeObjetGraphique(obj1);
    freeObjetGraphique(obj2);
    freeObjetGraphique(obj3);

    int res = classReference->GetNbObjetGraphique(classReference);
    printf("  Final object count after freeing: %d (Expected: 0)\n", res);
    

    /***********************************
     *          INHERITANCE            *
    ************************************/
    printf("\n[Test 5 : Inheritance Constructor] - Cercle & Rectangle\n");

    Cercle* cercle = (Cercle*) malloc(sizeof(Cercle));
    ConstructorCercle(cercle);
    printf("  Cercle created: x = %d, y = %d, rayon = %d\n", 
           cercle->myClass->mySuperMetaClass->getX((ObjetGraphique*)cercle),
           cercle->myClass->mySuperMetaClass->getY((ObjetGraphique*)cercle),
           cercle->myClass->getRadius(cercle));


    Rectangle* rectangle = (Rectangle*) malloc(sizeof(Rectangle));
    ConstructorRectangle(rectangle);
    printf("  Rectangle created : x = %d, y = %d, width = %d, height = %d\n", 
           rectangle->myClass->mySuperMetaClass->getX((ObjetGraphique*)rectangle),
           rectangle->myClass->mySuperMetaClass->getY((ObjetGraphique*)rectangle),
           rectangle->myClass->getWidth(rectangle),
           rectangle->myClass->getHeight(rectangle));

     printf("\n[Test 6: Accessing derived attributes] - Cercle & Rectangle\n");
     cercle->myClass->setRadius(cercle, 17);
     printf(" [Cercle] Updated radius = %d (Expected: 17)\n", cercle->myClass->getRadius(cercle));
     rectangle->myClass->setWidth(rectangle, 14);
     rectangle->myClass->setHeight(rectangle, 32);
     printf(" [Rectangle] Updated width = %d, height = %d (Expected: 14, 32)\n", 
     rectangle->myClass->getWidth(rectangle), rectangle->myClass->getHeight(rectangle));

     printf("\n[Test 7: Casting]\n");
     ObjetGraphique* objFromCercle = (ObjetGraphique*) cercle;
     ObjetGraphique* objFromRectangle = (ObjetGraphique*) rectangle;

     objFromCercle->myClass->setX(objFromCercle, 15);
     objFromRectangle->myClass->setX(objFromRectangle, 25);
     printf(" Cercle x after casting to base: %d (Expected: 15)\n", objFromCercle->myClass->getX(objFromCercle));
     printf(" Rectangle x after casting to base: %d (Expected: 25)\n", objFromRectangle->myClass->getX(objFromRectangle));


     free(cercle);
     free(rectangle);

    /***********************************
     *          POLYMORPHISM            *
    ************************************/

    Cercle * cercle2 = (Cercle *) malloc(sizeof(Cercle));
    ConstructorCercle(cercle2);
    cercle2->myClass->setRadius(cercle2, 10);

    printf("\n[Test 8 : Polymorphism] effacer((ObjetGraphique*) rectangle);- Cercle:\n");
    afficher((ObjetGraphique*) cercle2);
    deplacer((ObjetGraphique*) cercle2);
    effacer((ObjetGraphique*) cercle2);

    Rectangle * rectangle2 = (Rectangle *) malloc(sizeof(Rectangle));
    ConstructorRectangle(rectangle2);
    rectangle2->myClass->setWidth(rectangle2, 5);
    rectangle2->myClass->setHeight(rectangle2, 10);

    printf("\n[Test 9 : Polymorphism] - Rectangle\n");
    afficher((ObjetGraphique *) rectangle2);
    deplacer((ObjetGraphique*) rectangle2);
    effacer((ObjetGraphique*) rectangle2);

    free(cercle2);
    free(rectangle2);

    return 0;
}