#ifndef BLOOM_H
#define BLOOM_H

#include "ofMain.h"
#include "Petal.h"

class Bloom
{
    public:
        Bloom();

        void setup(ofVec3f *_bloomPoint);
        void update();
        void draw();
        void clear();

        ofVec3f bloomPoint;
    int step = (int(ofRandom(10,60)));


        vector <Petal *> petals;

        virtual ~Bloom();
    protected:
    private:
};

#endif // BLOOM_H
