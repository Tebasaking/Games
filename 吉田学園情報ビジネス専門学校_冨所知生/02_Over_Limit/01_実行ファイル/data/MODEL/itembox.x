xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 180;
 1.60888;7.06722;-4.70776;,
 4.82664;7.06722;-4.70776;,
 4.82664;5.34804;-4.70776;,
 1.60888;5.34804;-4.70776;,
 4.82664;3.62885;-4.70776;,
 1.60888;3.62885;-4.70776;,
 4.82664;1.90967;-4.70776;,
 1.60888;1.90967;-4.70776;,
 4.82664;0.19048;-4.70776;,
 1.60888;0.19048;-4.70776;,
 4.82664;7.06722;-1.56925;,
 4.82664;5.34804;-1.56925;,
 4.82664;7.06722;1.56925;,
 4.82664;5.34804;1.56925;,
 4.82664;7.06722;4.70776;,
 4.82664;5.34804;4.70776;,
 4.82664;3.62885;-1.56925;,
 4.82664;3.62885;1.56925;,
 4.82664;3.62885;4.70776;,
 4.82664;1.90967;-1.56925;,
 4.82664;1.90967;1.56925;,
 4.82664;1.90967;4.70776;,
 4.82664;0.19048;-1.56925;,
 4.82664;0.19048;1.56925;,
 4.82664;0.19048;4.70776;,
 1.60888;7.06722;4.70776;,
 1.60888;5.34804;4.70776;,
 1.60888;3.62885;4.70776;,
 1.60888;1.90967;4.70776;,
 1.60888;0.19048;4.70776;,
 1.60888;7.06722;1.56925;,
 1.60888;7.06722;-1.56925;,
 1.60888;0.19048;1.56925;,
 1.60888;0.19048;-1.56925;,
 1.83394;7.97592;-5.36632;,
 5.50183;7.97592;-5.36632;,
 5.50183;7.06342;-5.36632;,
 1.83394;7.06342;-5.36632;,
 5.50183;7.97592;-1.78877;,
 5.50183;7.06342;-1.78877;,
 5.50183;7.97592;1.78877;,
 5.50183;7.06342;1.78877;,
 5.50183;7.97592;5.36632;,
 5.50183;7.06342;5.36632;,
 1.83394;7.97592;5.36632;,
 1.83394;7.06342;5.36632;,
 1.83394;7.97592;1.78877;,
 1.83394;7.97592;-1.78877;,
 1.83394;7.06342;1.78877;,
 1.83394;7.06342;-1.78877;,
 3.66073;8.97062;3.10005;,
 4.58573;8.97062;3.10005;,
 4.58573;6.29062;3.10005;,
 3.66073;6.29062;3.10005;,
 4.58573;8.97062;3.84005;,
 4.58573;6.29062;3.84005;,
 3.66073;8.97062;3.84005;,
 3.66073;6.29062;3.84005;,
 3.66073;8.97062;-4.48982;,
 4.58573;8.97062;-4.48982;,
 4.58573;6.29062;-4.48982;,
 3.66073;6.29062;-4.48982;,
 4.58573;8.97062;-3.74982;,
 4.58573;6.29062;-3.74982;,
 3.66073;8.97062;-3.74982;,
 3.66073;6.29062;-3.74982;,
 2.46314;6.02945;-4.85094;,
 3.54814;6.02945;-4.85094;,
 3.54814;0.22945;-4.85094;,
 2.46314;0.22945;-4.85094;,
 3.54814;6.02945;-4.54094;,
 3.54814;0.22945;-4.54094;,
 2.46314;6.02945;-4.54094;,
 2.46314;0.22945;-4.54094;,
 0.01405;5.96444;-4.85094;,
 3.60405;5.96444;-4.85094;,
 3.60405;4.96444;-4.85094;,
 0.01405;4.96444;-4.85094;,
 3.60405;5.96444;-4.54094;,
 3.60405;4.96444;-4.54094;,
 0.01405;5.96444;-4.54094;,
 0.01405;4.96444;-4.54094;,
 -0.04282;5.00933;-4.85094;,
 2.50718;5.00933;-4.85094;,
 2.50718;0.27433;-4.85094;,
 -0.04282;0.27433;-4.85094;,
 2.50718;5.00933;-4.54094;,
 2.50718;0.27433;-4.54094;,
 -0.04282;5.00933;-4.54094;,
 -0.04282;0.27433;-4.54094;,
 -1.60888;5.34804;-4.70776;,
 -4.82664;5.34804;-4.70776;,
 -4.82664;7.06722;-4.70776;,
 -1.60888;7.06722;-4.70776;,
 -1.60888;3.62885;-4.70776;,
 -4.82664;3.62885;-4.70776;,
 -1.60888;1.90967;-4.70776;,
 -4.82664;1.90967;-4.70776;,
 -1.60888;0.19048;-4.70776;,
 -4.82664;0.19048;-4.70776;,
 -4.82664;5.34804;-1.56925;,
 -4.82664;7.06722;-1.56925;,
 -4.82664;5.34804;1.56925;,
 -4.82664;7.06722;1.56925;,
 -4.82664;5.34804;4.70776;,
 -4.82664;7.06722;4.70776;,
 -4.82664;3.62885;-1.56925;,
 -4.82664;3.62885;1.56925;,
 -4.82664;3.62885;4.70776;,
 -4.82664;1.90967;-1.56925;,
 -4.82664;1.90967;1.56925;,
 -4.82664;1.90967;4.70776;,
 -4.82664;0.19048;-1.56925;,
 -4.82664;0.19048;1.56925;,
 -4.82664;0.19048;4.70776;,
 -1.60888;5.34804;4.70776;,
 -1.60888;7.06722;4.70776;,
 -1.60888;3.62885;4.70776;,
 -1.60888;1.90967;4.70776;,
 -1.60888;0.19048;4.70776;,
 -1.60888;7.06722;1.56925;,
 -1.60888;7.06722;-1.56925;,
 -1.60888;0.19048;1.56925;,
 -1.60888;0.19048;-1.56925;,
 -1.83394;7.06342;-5.36632;,
 -5.50183;7.06342;-5.36632;,
 -5.50183;7.97592;-5.36632;,
 -1.83394;7.97592;-5.36632;,
 -5.50183;7.06342;-1.78877;,
 -5.50183;7.97592;-1.78877;,
 -5.50183;7.06342;1.78877;,
 -5.50183;7.97592;1.78877;,
 -5.50183;7.06342;5.36632;,
 -5.50183;7.97592;5.36632;,
 -1.83394;7.06342;5.36632;,
 -1.83394;7.97592;5.36632;,
 -1.83394;7.97592;1.78877;,
 -1.83394;7.97592;-1.78877;,
 -1.83394;7.06342;1.78877;,
 -1.83394;7.06342;-1.78877;,
 -3.66073;6.29062;3.10005;,
 -4.58573;6.29062;3.10005;,
 -4.58573;8.97062;3.10005;,
 -3.66073;8.97062;3.10005;,
 -4.58573;6.29062;3.84005;,
 -4.58573;8.97062;3.84005;,
 -3.66073;6.29062;3.84005;,
 -3.66073;8.97062;3.84005;,
 -3.66073;6.29062;-4.48982;,
 -4.58573;6.29062;-4.48982;,
 -4.58573;8.97062;-4.48982;,
 -3.66073;8.97062;-4.48982;,
 -4.58573;6.29062;-3.74982;,
 -4.58573;8.97062;-3.74982;,
 -3.66073;6.29062;-3.74982;,
 -3.66073;8.97062;-3.74982;,
 -2.46314;0.22945;-4.85094;,
 -3.54814;0.22945;-4.85094;,
 -3.54814;6.02945;-4.85094;,
 -2.46314;6.02945;-4.85094;,
 -3.54814;0.22945;-4.54094;,
 -3.54814;6.02945;-4.54094;,
 -2.46314;0.22945;-4.54094;,
 -2.46314;6.02945;-4.54094;,
 -0.01405;4.96444;-4.85094;,
 -3.60405;4.96444;-4.85094;,
 -3.60405;5.96444;-4.85094;,
 -0.01405;5.96444;-4.85094;,
 -3.60405;4.96444;-4.54094;,
 -3.60405;5.96444;-4.54094;,
 -0.01405;4.96444;-4.54094;,
 -0.01405;5.96444;-4.54094;,
 0.04282;0.27433;-4.85094;,
 -2.50718;0.27433;-4.85094;,
 -2.50718;5.00933;-4.85094;,
 0.04282;5.00933;-4.85094;,
 -2.50718;0.27433;-4.54094;,
 -2.50718;5.00933;-4.54094;,
 0.04282;0.27433;-4.54094;,
 0.04282;5.00933;-4.54094;;
 
 156;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;2,11,16,4;,
 4;11,13,17,16;,
 4;13,15,18,17;,
 4;4,16,19,6;,
 4;16,17,20,19;,
 4;17,18,21,20;,
 4;6,19,22,8;,
 4;19,20,23,22;,
 4;20,21,24,23;,
 4;14,25,26,15;,
 4;15,26,27,18;,
 4;18,27,28,21;,
 4;21,28,29,24;,
 4;25,14,12,30;,
 4;30,12,10,31;,
 4;31,10,1,0;,
 4;32,23,24,29;,
 4;33,22,23,32;,
 4;9,8,22,33;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,42,40,46;,
 4;46,40,38,47;,
 4;47,38,35,34;,
 4;48,41,43,45;,
 4;49,39,41,48;,
 4;37,36,39,49;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,50,53,57;,
 4;56,54,51,50;,
 4;53,52,55,57;,
 4;58,59,60,61;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;64,58,61,65;,
 4;64,62,59,58;,
 4;61,60,63,65;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 4;72,66,69,73;,
 4;72,70,67,66;,
 4;69,68,71,73;,
 4;74,75,76,77;,
 4;75,78,79,76;,
 4;78,80,81,79;,
 4;80,74,77,81;,
 4;80,78,75,74;,
 4;77,76,79,81;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
 4;88,82,85,89;,
 4;88,86,83,82;,
 4;85,84,87,89;,
 4;90,91,92,93;,
 4;94,95,91,90;,
 4;96,97,95,94;,
 4;98,99,97,96;,
 4;91,100,101,92;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;95,106,100,91;,
 4;106,107,102,100;,
 4;107,108,104,102;,
 4;97,109,106,95;,
 4;109,110,107,106;,
 4;110,111,108,107;,
 4;99,112,109,97;,
 4;112,113,110,109;,
 4;113,114,111,110;,
 4;104,115,116,105;,
 4;108,117,115,104;,
 4;111,118,117,108;,
 4;114,119,118,111;,
 4;120,103,105,116;,
 4;121,101,103,120;,
 4;93,92,101,121;,
 4;119,114,113,122;,
 4;122,113,112,123;,
 4;123,112,99,98;,
 4;124,125,126,127;,
 4;125,128,129,126;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;136,131,133,135;,
 4;137,129,131,136;,
 4;127,126,129,137;,
 4;134,132,130,138;,
 4;138,130,128,139;,
 4;139,128,125,124;,
 4;140,141,142,143;,
 4;141,144,145,142;,
 4;144,146,147,145;,
 4;146,140,143,147;,
 4;143,142,145,147;,
 4;146,144,141,140;,
 4;148,149,150,151;,
 4;149,152,153,150;,
 4;152,154,155,153;,
 4;154,148,151,155;,
 4;151,150,153,155;,
 4;154,152,149,148;,
 4;156,157,158,159;,
 4;157,160,161,158;,
 4;160,162,163,161;,
 4;162,156,159,163;,
 4;159,158,161,163;,
 4;162,160,157,156;,
 4;164,165,166,167;,
 4;165,168,169,166;,
 4;168,170,171,169;,
 4;170,164,167,171;,
 4;167,166,169,171;,
 4;170,168,165,164;,
 4;172,173,174,175;,
 4;173,176,177,174;,
 4;176,178,179,177;,
 4;178,172,175,179;,
 4;175,174,177,179;,
 4;178,176,173,172;,
 4;3,90,93,0;,
 4;5,94,90,3;,
 4;7,96,94,5;,
 4;9,98,96,7;,
 4;25,116,115,26;,
 4;26,115,117,27;,
 4;27,117,118,28;,
 4;28,118,119,29;,
 4;30,120,116,25;,
 4;31,121,120,30;,
 4;0,93,121,31;,
 4;29,119,122,32;,
 4;32,122,123,33;,
 4;33,123,98,9;,
 4;37,124,127,34;,
 4;44,135,134,45;,
 4;46,136,135,44;,
 4;47,137,136,46;,
 4;34,127,137,47;,
 4;45,134,138,48;,
 4;48,138,139,49;,
 4;49,139,124,37;;
 
 MeshMaterialList {
  4;
  156;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1;;
  Material {
   0.269804;0.222745;0.241569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.219608;0.194510;0.200784;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.718431;0.348235;0.250980;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.332549;0.009412;0.009412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;;
  156;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;;
 }
}
