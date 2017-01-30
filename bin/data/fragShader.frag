// fragment shader
#version 150

out vec4 outputColor;
//uniform vec2 vecPos0, vecPos1, vecPos2, vecPos3, vecPos4, vecPos5, vecPos6;
uniform vec2 windowSize;

// //Shader Function and where position is defined
// float distVal (int pixY, int pixX) {
//     float pixDist;
//     float outCol;
//     for (int i = 0; i < vecNum; i++) {
//        pixDist = ofDist(pos[i].x, pos[i].y, pixY, pixX);
//        pixDist = sqrt(pow((vecPos0.y - pointvect[i + 1].y), 2) + pow((pointvect[i].x - pointvect[i + 1].x), 2));
//        out += maxDist/pixDist;
//    }
//    return outCol;
// }
//
// void shaderVis() {
//    //Shader Calulations
//    pixCount = 0;
//    for (int x = 0; x < ofGetWidth(); x++) {
//        for (int y = 0; y < ofGetHeight(); y++) {
//            distCol = distVal(y, x) * 70;
//            int loc = x + y * ofGetWidth();
//            pixels.setColor(loc, ofColor(distCol*2, distCol*3, distCol*4));
//            pixCount+=1;
//        }
//    }
// }


void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

    float windowWidth = windowSize.x;
    float windowHeight = windowSize.y;

    float r = gl_FragCoord.x / windowWidth;
    float g = gl_FragCoord.y / windowHeight;
    float b = 1.0;
    float a = 0.9;
    outputColor = vec4(r, g, b, a);


}
