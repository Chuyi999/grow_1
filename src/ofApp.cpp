#include "ofApp.h"

//--------------------------------------------------------------
//
//bool removeTest( int & radius){
////    return radius =0;
//}

void ofApp::setup(){
    ofSetFrameRate(20);
    ofSetVerticalSync(true);
    ofBackground(0);

    ofToggleFullscreen();
    ofEnableDepthTest();

    record = false;

    dragStart = false;

    recStart = 0;

    float posFactor = ofGetWidth()/2*ofRandomf();
            posFactor *= posFactor*posFactor*0.1;
            float distanceFactor = ofGetHeight()*ofRandomf();
            float bXPos = sin(posFactor)*distanceFactor;
            float bYPos = cos(posFactor)*distanceFactor;
            prevBloom = ofVec3f(bXPos,bYPos,ofRandomf()*30*-1);
            prevBloom = ofVec3f(0,0,0);



    light.setDiffuseColor(ofFloatColor(1.0,1.0,1.0));
    light.setPosition(ofPoint(0.0,0.0,400.0));
    
    
    mySound.load("nature.mp3");
     mySound.play();
    //mySound2.load("bubble.mp3");
   
  
    
    
    //--------------------------------------------opencv
   // ofSetFrameRate(20);
    mCamWidth = 1280;
    mCamHeight = 720;
    
    mVidGrabber. setDeviceID(0);
    mVidGrabber. setDesiredFrameRate(60);
    mVidGrabber. initGrabber(mCamWidth,mCamHeight);
    
    //Step 8 : Setup openCV objects / variables
    mColorImg.allocate(mCamWidth,mCamHeight);
    mGrayImage.allocate(mCamWidth,mCamHeight);
    mGrayBg.allocate(mCamWidth,mCamHeight);
    mGrayDiff.allocate(mCamWidth,mCamHeight);
    
    mThreshold = 80;
    mLearnBackground = true;
    
    //----------------------number
    mPos = ofVec2f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
    

    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < trees.size(); i++){
        trees[i]->update();
    }

        for (int i = 0; i< bloomsMain.size(); i++){
        bloomsMain[i]->update();

    }
    
    
    //--------------------------------------------opencv
    mVidGrabber.update();
    
       if (mVidGrabber.isFrameNew()){
        
        mColorImg.setFromPixels(mVidGrabber.getPixels());
        
    
        mGrayImage = mColorImg;
        
        if(mLearnBackground == true) {
            // mGrayBg = mGrayImage;
            mLearnBackground = false;
        }
        
        mGrayDiff.absDiff(mGrayBg,mGrayImage);
        mGrayDiff.threshold(mThreshold);
        
        mContourFinder.findContours(mGrayDiff, 10, (mCamWidth * mCamHeight)*50, 2, false);
     
        
    }
   
    
    for(int i = 0; i < mContourFinder.nBlobs; i++) {
        
        ofRectangle r = mContourFinder.blobs.at(i).boundingRect;
        
        if(r.x<(ofGetWidth()/2+100*8)&&r.x>(ofGetWidth()/2-100*8)&&r.y<(ofGetHeight()/2+100*8)&&r.y>(ofGetHeight()/2-100*8)){
            
            
            ofVec3f bloomInit = ofVec3f(cos(theta)*radius + ofGetWidth()/2,sin(theta)*radius+ofGetHeight()/2,ofRandomf()*200*-1);
            makeBloom(bloomInit);
            prevBloom = bloomInit;
            cout<<"prevBloom" <<endl;
            
            theta ++;
            //radius ++;
            // mySound2.play();
            radius ++;
            
            drawflower= true;
            mySound.setVolume(0.8);
            
          

        }else{
            ofBackground(0);
           // radius --;
            mySound.setVolume(0.1);

           
            drawflower= false;
//            radius =100;
//          radius++;
//            theta ++;
////
            
        }
        }
}

    




//--------------------------------------------------------------
void ofApp::draw(){

    
    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,30);
    
    for (int i = 0; i < trees.size(); i++){
        trees[i]->draw();
        
    }

   
    if (record == true){
        string frameCount = ofToString(20000+ofGetFrameNum());
        string fileName = "filmImages/" + currentDate + "/" + frameCount + ".png";
        ofSaveScreen(fileName);

        int recFrames = ofGetFrameNum()-recStart;
        float recTime = recFrames / 60;

        cout << "Frames: " << recFrames << endl;
        cout << "Time: " << recTime << endl;
    }

       
    //---------------------------------------opencv
    

   // ofSetColor(255);
    
//    
   // mContourFinder.draw(0,0);
    
//    ofRectangle r = mContourFinder.blobs.at(0).boundingRect;

//
//        int XPos = mContourFinder.blobs[0].boundingRect.getCenter().x;
//        int YPos = mContourFinder.blobs[0].boundingRect.getCenter().y;
   
    
//    for (int i = 0; i< 500; i++){
//        theta++;
//        radius++;
//    }
    if(drawflower== true){
    for (int i = 0; i< bloomsMain.size(); i++){
    
            bloomsMain[i]->draw();
    
    }
    }else{
    
        bloomsMain.clear();
        radius=100;
        

    }
    
    
//        for(int i = 0; i < mContourFinder.nBlobs; i++) {
//
//            ofRectangle r = mContourFinder.blobs.at(i).boundingRect;
//            
//        if(r.x<(ofGetWidth()/2+100*5)&&r.x>(ofGetWidth()/2-100*5)&&r.y<(ofGetHeight()/2+100*5)&&r.y>(ofGetHeight()/2-100*5)){
//            ofVec3f bloomInit = ofVec3f(cos(theta)*radius + ofGetWidth()/2,sin(theta)*radius+ofGetHeight()/2,ofRandomf()*200*-1);
//            makeBloom(bloomInit);
//            prevBloom = bloomInit;
//            cout<<"prevBloom" <<endl;
//        for (int i = 0; i< bloomsMain.size(); i++){
//            bloomsMain[i]->draw();
//        }
//        }else{
//            ofBackground(0);
//            
//        
//        }
//        }
//    
//    for(int i = 0; i < mContourFinder.nBlobs; i++) {
//        ofRectangle r = mContourFinder.blobs.at(i).boundingRect;
//        r.x += 320; r.y += 240;
//    }
    
    
    
//    for(int i = 0; i < mContourFinder.nBlobs;i++){
//        
//        mContourFinder.blobs[i].draw(20,540);
//        
//        if( mContourFinder.blobs[i].hole){
//            ofDrawBitmapString("hole", mContourFinder.blobs[i].boundingRect.getCenter().x + 20, mContourFinder.blobs[i].boundingRect.getCenter().y + 540);
//            
//        }
//        
//    }
    

//
//    mVidGrabber.draw(20,540);

//     mGrayDiff.draw(0,0);
//    int numblobs = int(ofRandom(1,mContourFinder.nBlobs));
//      ofVec2f linebetween = mContourFinder.blobs[numblobs].boundingRect.getCenter() - mContourFinder.blobs[numblobs-1].boundingRect.getCenter();
//    float theta = atan2(linebetween.x, linebetween.y)-(PI/2);
//    int XPos = mContourFinder.blobs[numblobs].boundingRect.getCenter().x;
//    int YPos = mContourFinder.blobs[numblobs].boundingRect.getCenter().y;
//    
//
//    if  ( XPos == ofGetWidth()/2 ){
//        
//        int XPos = mContourFinder.blobs[numblobs].boundingRect.getCenter().x;
//        int YPos = mContourFinder.blobs[numblobs].boundingRect.getCenter().y;
//        
//        //        cout<< "num"<<numblobs<<endl;
//        
//        
//      
//        
//        //float theta = atan2(linebetween.x, linebetween.y)-(PI/2);
//        
//        float posFactor = ofGetWidth()/5*ofRandomf();
//        posFactor *= posFactor*posFactor*0.1;
//        float distanceFactor = ofGetHeight()*ofRandomf();
//        float bXPos =ofGetWidth()*sin(ofRandomf());
//        float bYPos = ofGetHeight()/2*cos(ofRandomf());
//        
//        
//        
//        float bZPos = ofRandomf()*200*-1;
//        
//        ofVec3f bloomInit = ofVec3f(bXPos,bYPos,bZPos);
//        
//        ofVec3f treeInit = ofVec3f(bXPos,bYPos,bZPos-10);
//        
//        for (int i=0; i<ofRandom(1,4); i++){
//            Tree *t = new Tree();
//            int angleInit = int(ofRandomuf()*360);
//            //int treeInit = int(ofRandomf()*theta);
//            
//            t->setup(&treeInit,&angleInit,trees.size());
//            //t>update(mContourFinder.blobs[numblobs].boundingRect.getCenter());
//            trees.push_back(t);
//        }
//        
//        makeBloom(bloomInit);
//        prevBloom = bloomInit;
//        
//    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if  (key == ' '){
    int numblobs = int(ofRandom(1,mContourFinder.nBlobs));
    
    int XPos = mContourFinder.blobs[numblobs].boundingRect.getCenter().x;
    int YPos = mContourFinder.blobs[numblobs].boundingRect.getCenter().y;
    
    //        cout<< "num"<<numblobs<<endl;
    
    
    ofVec2f linebetween = mContourFinder.blobs[numblobs].boundingRect.getCenter() - mContourFinder.blobs[numblobs-1].boundingRect.getCenter();
    
    //float theta = atan2(linebetween.x, linebetween.y)-(PI/2);
    
        float posFactor = ofGetWidth()/5*ofRandomf();
        posFactor *= posFactor*posFactor*0.1;
        float distanceFactor = ofGetHeight()*ofRandomf();
        float bXPos =ofGetWidth()*sin(ofRandomf());
        float bYPos = ofGetHeight()/2*cos(ofRandomf());
     
        
        
    float bZPos = ofRandomf()*200*-1;
    
    ofVec3f bloomInit = ofVec3f(bXPos*ofRandomf() ,bYPos*ofRandomf(),bZPos);
    
    ofVec3f treeInit = ofVec3f(bXPos,bYPos,bZPos-10);
//    
//    for (int i=0; i<ofRandom(1,4); i++){
//        Tree *t = new Tree();
//        int angleInit = int(ofRandomuf()*360);
//        //int treeInit = int(ofRandomf()*theta);
//        
//        t->setup(&treeInit,&angleInit,trees.size());
//        //t>update(mContourFinder.blobs[numblobs].boundingRect.getCenter());
//        trees.push_back(t);
//    }
//
    makeBloom(bloomInit);
    prevBloom = bloomInit;
//
    
//}

 
        if(key == 'f'){
        ofToggleFullscreen();
    }
        
    if (key == 's'){
        string frameCount = ofToString(20000+ofGetFrameNum());
        string fileName = "Images/" + frameCount + ".jpg";
        ofSaveScreen(fileName);
    }

    //THIS CREATES A NEW TREE... MAINLY FOR TESTING
    if(key == 't'){
        ofVec3f treeInit = ofVec3f(0,ofGetHeight()*ofRandom(0.1,0.9),0);
        int angleInit = int(ofRandom(70,130));

        Tree *t = new Tree();
        t->setup(&treeInit,&angleInit,trees.size());
        trees.push_back(t);
    }

    //CREATES A NEW BLOOM -- ALSO FOR TESTING
    if(key == 'b'){
            float posFactor = ofGetWidth()/2*ofRandomf();
            //posFactor *= posFactor*posFactor*0.1;
            float distanceFactor = ofGetHeight()*ofRandomf();
            float bXPos = sin(posFactor)*distanceFactor;
            float bYPos = cos(posFactor)*distanceFactor;
            ofVec3f bloomInit = ofVec3f(bXPos,bYPos,ofRandomf()*30*-1);

            ofVec3f dist = prevBloom - bloomInit;
            float distanceFromPrev = dist.length();

            float chance = ofGetHeight()*ofRandomf()*0.5;
            float minDist = 20;

        if (prevBloom != ofVec3f(0,0,0)){
            while (distanceFromPrev > chance || distanceFromPrev < minDist){
                distanceFactor = ofGetHeight()*ofRandomf();
                bXPos = sin(posFactor)*distanceFactor;
                bYPos = cos(posFactor)*distanceFactor;
                bloomInit = ofVec3f(bXPos,bYPos,ofRandomf()*30*-1);
                dist = prevBloom - bloomInit;
                distanceFromPrev = dist.length();
                chance = ofGetHeight()*ofRandomf()*2;
            }
        }

        makeBloom(bloomInit);

        prevBloom = bloomInit;

    }

    
    if(key == 'r'){
            record = true;
            recStart = ofGetFrameNum();
            currentDate = ofGetTimestampString();
        }

    if(key == 'e'){
            record = false;
    }

    
    }
}

//--------------------------------------------------------------
void ofApp::makeBloom(ofVec3f _bloomInit){

            Bloom * b = new Bloom();
            b->setup(&_bloomInit);
            bloomsMain.push_back(b);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
