#include <stdio.h>
#include <stdlib.h>

#include "objet_graphique.h"

// Method : set X for an ObjetGraphique object
void setX(ObjetGraphique* this_, int x)
{
    this_->x = x;
}

// Method : set Y for an ObjetGraphique object
void setY(ObjetGraphique* this_, int y)
{
    this_->y = y;
}

// Method : get X for an ObjetGraphique object
int getX(ObjetGraphique* this_)
{
    return this_->x;
}

// Method : get Y for an ObjetGraphique object
int getY(ObjetGraphique* this_)
{
    return this_->y;
}

// Method : get the number of ObjetGraphique's instances
int GetNbObjetGraphique(MetaObjetGraphique* this_)
{
    return this_->NbObjetGraphique;
}

// Constructor (ObjetGraphique)
void ConstructorObjetGraphique(ObjetGraphique* this_)
{
    this_->x = 0;
    this_->y = 0;
}

/*********************************
 *           CERCLE
*********************************/

void setRadius(Cercle* this_, int radius) {
    this_->radius = radius;
}

int getRadius(Cercle* this_) {
    return this_->radius;
}


/*********************************
 *           RECTANGLE
*********************************/

void setWidth(Rectangle* this_, int width) {
    this_->width = width;
}

void setHeight(Rectangle* this_, int height) {
    this_->height = height;
}

int getWidth(Rectangle* this_) {
    return this_->width;
}

int getHeight(Rectangle* this_) {
    return this_->height;
}


static MetaObjetGraphique metaObjetGraphique = {
    .setX = setX,
    .setY = setY,
    .getX = getX,
    .getY = getY,
    .NbObjetGraphique = 0,
    .GetNbObjetGraphique = GetNbObjetGraphique,
    .ConstructorObjetGraphique = ConstructorObjetGraphique,

    // Initializing virtual method tables (TVM)
    .TVMeffacer = {
        effacerCercle,   
        effacerRectangle,
        effacer          
    },
    
    .TVMafficher = {
        afficherCercle,   
        afficherRectangle,
        afficher
    },
    
    .TVMdeplacer = {
        deplacerCercle,    
        deplacerRectangle,
        deplacer 
    }
};


// Cercle

void ConstructorCercle(Cercle* this_) {
    this_->myClass = (MetaCercle*) malloc(sizeof(MetaCercle));

    this_->myClass->mySuperMetaClass = &metaObjetGraphique; 
    this_->myClass->ConstructorCercle = ConstructorCercle;
    this_->myClass->setRadius = setRadius;
    this_->myClass->getRadius = getRadius;
    this_->myClass->mySuperMetaClass->ConstructorObjetGraphique((ObjetGraphique*) this_);
    
    this_->radius = 0; 

    this_->mySuperClass.type = 0;
}

void afficherCercle(ObjetGraphique * this_)
{
    Cercle * thisCercle_ = (Cercle*) this_;
    printf("[afficherCercle] : affichage cercle de rayon = %d\n", thisCercle_->radius); 
}

void deplacerCercle(ObjetGraphique * this_)
{
    Cercle * thisCercle_ = (Cercle*) this_;
    printf("[deplacerCercle] : deplacer cercle de rayon = %d\n", thisCercle_->radius); 
}

void effacerCercle(ObjetGraphique * this_)
{
    Cercle * thisCercle_ = (Cercle*) this_;
    printf("[effacerCercle] : effacer cercle de rayon = %d\n", thisCercle_->radius); 
}

// Rectangle
void ConstructorRectangle(Rectangle* this_) {
    this_->myClass = (MetaRectangle*) malloc(sizeof(MetaRectangle));

    this_->myClass->mySuperMetaClass = &metaObjetGraphique; 
    this_->myClass->ConstructorRectangle = ConstructorRectangle;
    this_->myClass->setWidth  = setWidth;
    this_->myClass->setHeight = setHeight;
    
    this_->myClass->getWidth = getWidth;
    this_->myClass->getHeight = getHeight;

    this_->myClass->mySuperMetaClass->ConstructorObjetGraphique((ObjetGraphique*) this_);

    this_->width = 0; 
    this_->height = 0;

    this_->mySuperClass.type = 1;
}

void afficherRectangle(ObjetGraphique * this_)
{
    Rectangle * thisRectangle_ = (Rectangle *) this_;
    printf("[afficherRectangle] : affichage rectangle de largeur = %d, longueur = %d\n", thisRectangle_->width, thisRectangle_->height);
}

void deplacerRectangle(ObjetGraphique * this_)
{
    Rectangle * thisRectangle_ = (Rectangle *) this_;
    printf("[afficherRectangle] : deplacer rectangle de largeur = %d, longueur = %d\n", thisRectangle_->width, thisRectangle_->height);
}

void effacerRectangle(ObjetGraphique * this_)
{
    Rectangle * thisRectangle_ = (Rectangle *) this_;
    printf("[effacerRectangle] : effacer rectangle de largeur = %d, longueur = %d\n", thisRectangle_->width, thisRectangle_->height);
}


// Function : create a new ObjetGraphique object with default value (default constructor)
ObjetGraphique* createDefaultObjetGraphique() {
    ObjetGraphique* obj = (ObjetGraphique *) malloc(sizeof(ObjetGraphique));

    if (obj) {
        obj->myClass = &metaObjetGraphique;
        obj->myClass->ConstructorObjetGraphique(obj); 
        obj->myClass->NbObjetGraphique++;
    }

    return obj;
}

// Function : create a new ObjetGraphique object (ad hoc)
ObjetGraphique* createObjetGraphique(int x, int y)
{
    ObjetGraphique* obj = (ObjetGraphique *) malloc(sizeof(ObjetGraphique));

    if (obj)
    {
        obj->myClass = &metaObjetGraphique;
        obj->myClass->ConstructorObjetGraphique(obj);
        obj->myClass->setX(obj, x);
        obj->myClass->setY(obj, y);
        obj->myClass->NbObjetGraphique++;
    }

    return obj;
}

void freeObjetGraphique(ObjetGraphique* objet) {
    if (objet) {
        objet->myClass->NbObjetGraphique--; 
        free(objet);
        objet = NULL;
    }
}

void afficher(ObjetGraphique * this_)
{
    return metaObjetGraphique.TVMafficher[this_->type](this_);
}

void deplacer(ObjetGraphique * this_)
{
    return metaObjetGraphique.TVMdeplacer[this_->type](this_);
}

void effacer(ObjetGraphique * this_)
{
    return metaObjetGraphique.TVMeffacer[this_->type](this_);
}


void initMOG(struct MetaObjetGraphique* mog)
{
    mog->TVMeffacer [OG]        = effacer;
    mog->TVMeffacer[CERCLE]     = effacerCercle;
    mog->TVMeffacer[RECTANGLE]  = effacerRectangle;

    mog->TVMafficher[OG]        = afficher;
    mog->TVMafficher[CERCLE]    = afficherCercle;
    mog->TVMafficher[RECTANGLE] = afficherRectangle;

    mog->TVMdeplacer[OG]        = deplacer;
    mog->TVMdeplacer[CERCLE]    = deplacerCercle;
    mog->TVMdeplacer[RECTANGLE] = deplacerRectangle;
 
    mog->effacer  = mog->TVMeffacer[OG];   
    mog->afficher = mog->TVMafficher[OG]; 
    mog->deplacer = mog->TVMdeplacer[OG];
}
