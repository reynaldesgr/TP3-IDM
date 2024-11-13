#ifndef OBJET_GRAPHIQUE_H
#define OBJET_GRAPHIQUE_H

#define NBCLASSES 3

/**********************************
            TYPEDEF                 
**********************************/
typedef struct ObjetGraphique ObjetGraphique;
typedef struct MetaObjetGraphique MetaObjetGraphique;

typedef struct Cercle Cercle;
typedef struct MetaCercle MetaCercle;

typedef struct Rectangle Rectangle;
typedef struct MetaRectangle MetaRectangle;

// Polymorphism
typedef enum OG_t { CERCLE=0, RECTANGLE=1, OG=2 } OG_t;

/**********************************/

// ObjetGraphique
struct ObjetGraphique {
    MetaObjetGraphique * myClass;
    
    // X coordinates
    int x;
    // Y coordinates 
    int y;

    // Type
    OG_t type;
};


struct MetaObjetGraphique {

    // Instance counter
    int NbObjetGraphique;

    // Class methods
    int (*GetNbObjetGraphique)(MetaObjetGraphique * this_);

    // Constructor
    void (*ConstructorObjetGraphique)(ObjetGraphique* this_);

    // Setter
    void (*setX)(ObjetGraphique* this_, int x);
    void (*setY)(ObjetGraphique* this_, int y);

    // Getter
    int (*getX)(ObjetGraphique* this_);
    int (*getY)(ObjetGraphique* this_);

    // TVMs 
    void (*TVMeffacer   [NBCLASSES])(ObjetGraphique* this_);
    void (*TVMafficher  [NBCLASSES])(ObjetGraphique* this_);
    void (*TVMdeplacer  [NBCLASSES])(ObjetGraphique* this_);
    int  (*TVMgetCentreX[NBCLASSES])(ObjetGraphique* this_);
    int  (*TVMgetCentreY[NBCLASSES])(ObjetGraphique* this_);

    // Pointers to call virtual methods
    void (*effacer)   (ObjetGraphique* this_);
    void (*afficher)  (ObjetGraphique* this_);
    void (*deplacer)  (ObjetGraphique* this_);

    int  (*getCentreX)(ObjetGraphique* this_);
    int  (*getCentreY)(ObjetGraphique* this_);
};

// Cercle
struct Cercle
{
    // Inheritance
    ObjetGraphique mySuperClass;

    MetaCercle* myClass;

    int radius; 
};

struct MetaCercle
{
    MetaObjetGraphique* mySuperMetaClass;

    // Constructor
    void (*ConstructorCercle)(Cercle* this_);

    // Methods
    void (*setRadius) (Cercle* this_, int radius);
    int  (*getRadius) (Cercle * this_);
};

// Rectangle
struct Rectangle
{
    // Inheritance
    ObjetGraphique mySuperClass;

    MetaRectangle* myClass;

    int width;
    int height;
};

struct MetaRectangle
{
    MetaObjetGraphique* mySuperMetaClass;

    // Constructor
    void (*ConstructorRectangle)(Rectangle* this_);

    // Methods
    void (*setWidth) (Rectangle* this_, int width);
    void (*setHeight)(Rectangle* this_, int height);
    int  (*getWidth) (Rectangle* this_);
    int  (*getHeight)(Rectangle* this_);
};


/******** FORWARDS METHOD DECLARATIONS ********/

// Declaration of generic methods
void setX                     (ObjetGraphique* this_, int x);
void setY                     (ObjetGraphique* this_, int y);
int  getX                     (ObjetGraphique* this_);
int  getY                     (ObjetGraphique* this_);
int  GetNbObjetGraphique      (MetaObjetGraphique* this_);
void ConstructorObjetGraphique(ObjetGraphique* this_);

// Declarations of specific methods
void setRadius (Cercle* this_, int radius);
int  getRadius (Cercle* this_);

void setWidth   (Rectangle* this_, int width);
void setHeight  (Rectangle* this_, int height);
int  getWidth   (Rectangle* this_);
int  getHeight  (Rectangle* this_);

// Declaration of constructors
void ConstructorCercle   (Cercle* this_);
void ConstructorRectangle(Rectangle * this_);

// Declaration of methods for managing graphic objects
ObjetGraphique* createDefaultObjetGraphique ();
ObjetGraphique* createObjetGraphique        (int x, int y);
void            freeObjetGraphique          (ObjetGraphique* objet);

// Initialization of virtual methods
void initMOG(MetaObjetGraphique* mog);

void afficherCercle   (ObjetGraphique * this_);
void afficherRectangle(ObjetGraphique * this_);
void afficher         (ObjetGraphique * this_);

void deplacerCercle   (ObjetGraphique * this_);
void deplacerRectangle(ObjetGraphique * this_);
void deplacer         (ObjetGraphique * this_);

void effacerCercle    (ObjetGraphique * this_);
void effacerRectangle (ObjetGraphique * this_);
void effacer          (ObjetGraphique * this_);

/*********************************************/

#endif // OBJET_GRAPHIQUE_H