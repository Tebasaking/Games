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
 108;
 -0.45802;0.92305;-1.21809;,
 0.05498;0.92305;-2.24409;,
 -0.30776;0.56030;-1.21809;,
 0.05498;0.92305;-2.24409;,
 0.05498;0.41005;-1.21809;,
 0.05498;0.92305;-2.24409;,
 0.41773;0.56030;-1.21809;,
 0.05498;0.92305;-2.24409;,
 0.56798;0.92305;-1.21809;,
 0.05498;0.92305;-2.24409;,
 0.41773;1.28580;-1.21809;,
 0.05498;0.92305;-2.24409;,
 0.05498;1.43605;-1.21809;,
 0.05498;0.92305;-2.24409;,
 -0.30776;1.28580;-1.21809;,
 0.05498;0.92305;-2.24409;,
 -0.45802;0.92305;-1.21809;,
 0.05498;0.92305;-1.21809;,
 -0.45802;0.92305;-1.21809;,
 -0.30776;0.56030;-1.21809;,
 0.05498;0.41005;-1.21809;,
 0.41773;0.56030;-1.21809;,
 0.56798;0.92305;-1.21809;,
 0.41773;1.28580;-1.21809;,
 0.05498;1.43605;-1.21809;,
 -0.30776;1.28580;-1.21809;,
 -0.44914;0.93169;-1.22124;,
 -0.36955;0.66062;-1.22124;,
 -0.36955;0.66062;-0.35491;,
 -0.44914;0.93169;-0.35491;,
 -0.15604;0.47562;-1.22124;,
 -0.15604;0.47562;-0.35491;,
 0.12359;0.43541;-1.22124;,
 0.12359;0.43541;-0.35491;,
 0.38057;0.55277;-1.22124;,
 0.38057;0.55277;-0.35491;,
 0.53331;0.79043;-1.22124;,
 0.53331;0.79043;-0.35491;,
 0.53331;1.07295;-1.22124;,
 0.53331;1.07295;-0.35491;,
 0.38057;1.31061;-1.22124;,
 0.38057;1.31061;-0.35491;,
 0.12359;1.42797;-1.22124;,
 0.12359;1.42797;-0.35491;,
 -0.15604;1.38776;-1.22124;,
 -0.15604;1.38776;-0.35491;,
 -0.36955;1.20276;-1.22124;,
 -0.36955;1.20276;-0.35491;,
 -0.44914;0.93169;-1.22124;,
 -0.44914;0.93169;-0.35491;,
 -0.36955;0.66062;0.51143;,
 -0.44914;0.93169;0.51142;,
 -0.15604;0.47562;0.51143;,
 0.12359;0.43541;0.51143;,
 0.38057;0.55277;0.51143;,
 0.53331;0.79043;0.51143;,
 0.53331;1.07295;0.51142;,
 0.38057;1.31061;0.51142;,
 0.12359;1.42797;0.51142;,
 -0.15604;1.38776;0.51142;,
 -0.36955;1.20276;0.51142;,
 -0.44914;0.93169;0.51142;,
 -0.36955;0.66062;1.37776;,
 -0.44914;0.93169;1.37776;,
 -0.15604;0.47562;1.37776;,
 0.12359;0.43541;1.37776;,
 0.38057;0.55277;1.37776;,
 0.53331;0.79043;1.37776;,
 0.53331;1.07295;1.37776;,
 0.38057;1.31061;1.37776;,
 0.12359;1.42797;1.37776;,
 -0.15604;1.38776;1.37776;,
 -0.36955;1.20276;1.37776;,
 -0.44914;0.93169;1.37776;,
 -0.36955;0.66062;2.24409;,
 -0.44914;0.93169;2.24409;,
 -0.15604;0.47562;2.24409;,
 0.12359;0.43541;2.24409;,
 0.38057;0.55277;2.24409;,
 0.53331;0.79043;2.24409;,
 0.53331;1.07295;2.24409;,
 0.38057;1.31061;2.24409;,
 0.12359;1.42797;2.24409;,
 -0.15604;1.38776;2.24409;,
 -0.36955;1.20276;2.24409;,
 -0.44914;0.93169;2.24409;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;-1.22124;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;,
 0.05224;0.93169;2.24409;;
 
 82;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;29,28,50,51;,
 4;28,31,52,50;,
 4;31,33,53,52;,
 4;33,35,54,53;,
 4;35,37,55,54;,
 4;37,39,56,55;,
 4;39,41,57,56;,
 4;41,43,58,57;,
 4;43,45,59,58;,
 4;45,47,60,59;,
 4;47,49,61,60;,
 4;51,50,62,63;,
 4;50,52,64,62;,
 4;52,53,65,64;,
 4;53,54,66,65;,
 4;54,55,67,66;,
 4;55,56,68,67;,
 4;56,57,69,68;,
 4;57,58,70,69;,
 4;58,59,71,70;,
 4;59,60,72,71;,
 4;60,61,73,72;,
 4;63,62,74,75;,
 4;62,64,76,74;,
 4;64,65,77,76;,
 4;65,66,78,77;,
 4;66,67,79,78;,
 4;67,68,80,79;,
 4;68,69,81,80;,
 4;69,70,82,81;,
 4;70,71,83,82;,
 4;71,72,84,83;,
 4;72,73,85,84;,
 3;86,27,26;,
 3;87,30,27;,
 3;88,32,30;,
 3;89,34,32;,
 3;90,36,34;,
 3;91,38,36;,
 3;92,40,38;,
 3;93,42,40;,
 3;94,44,42;,
 3;95,46,44;,
 3;96,48,46;,
 3;97,75,74;,
 3;98,74,76;,
 3;99,76,77;,
 3;100,77,78;,
 3;101,78,79;,
 3;102,79,80;,
 3;103,80,81;,
 3;104,81,82;,
 3;105,82,83;,
 3;106,83,84;,
 3;107,84,85;;
 
 MeshMaterialList {
  1;
  82;
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
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  65;
  -0.894427;0.000000;-0.447214;,
  -0.632456;-0.632456;-0.447214;,
  0.000000;-0.894427;-0.447214;,
  0.632456;-0.632456;-0.447214;,
  0.894427;0.000000;-0.447214;,
  0.632455;0.632456;-0.447214;,
  0.000000;0.894427;-0.447214;,
  -0.632455;0.632456;-0.447214;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.841253;-0.540642;0.000000;,
  -0.415416;-0.909632;0.000000;,
  0.142315;-0.989821;0.000000;,
  0.654861;-0.755750;0.000000;,
  0.959493;-0.281733;-0.000000;,
  0.959493;0.281734;-0.000000;,
  0.654861;0.755750;-0.000000;,
  0.142313;0.989822;-0.000000;,
  -0.415416;0.909631;0.000000;,
  -0.841252;0.540643;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.841253;-0.540642;0.000000;,
  -0.415416;-0.909632;0.000000;,
  0.142315;-0.989821;0.000000;,
  0.654861;-0.755749;0.000000;,
  0.959493;-0.281733;-0.000000;,
  0.959493;0.281734;-0.000000;,
  0.654861;0.755750;-0.000000;,
  0.142313;0.989822;-0.000000;,
  -0.415416;0.909631;0.000000;,
  -0.841252;0.540643;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.841253;-0.540642;0.000000;,
  -0.415416;-0.909632;0.000000;,
  0.142315;-0.989821;-0.000000;,
  0.654861;-0.755749;0.000000;,
  0.959493;-0.281733;-0.000000;,
  0.959493;0.281734;-0.000000;,
  0.654861;0.755750;-0.000000;,
  0.142313;0.989822;-0.000000;,
  -0.415416;0.909631;0.000000;,
  -0.841252;0.540642;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.841253;-0.540642;0.000000;,
  -0.415416;-0.909632;0.000000;,
  0.142315;-0.989821;0.000000;,
  0.654861;-0.755749;-0.000000;,
  0.959493;-0.281733;-0.000000;,
  0.959493;0.281734;-0.000000;,
  0.654861;0.755750;-0.000000;,
  0.142313;0.989822;-0.000000;,
  -0.415416;0.909631;0.000000;,
  -0.841252;0.540643;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.841253;-0.540642;0.000000;,
  -0.415416;-0.909632;0.000000;,
  0.142315;-0.989821;0.000000;,
  0.654861;-0.755749;0.000000;,
  0.959493;-0.281733;-0.000000;,
  0.959493;0.281734;-0.000000;,
  0.654861;0.755750;-0.000000;,
  0.142313;0.989822;-0.000000;,
  -0.415416;0.909631;0.000000;,
  -0.841252;0.540643;0.000000;;
  82;
  3;0,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,4;,
  3;4,5,5;,
  3;5,5,6;,
  3;6,7,7;,
  3;7,7,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  4;10,11,22,21;,
  4;11,12,23,22;,
  4;12,13,24,23;,
  4;13,14,25,24;,
  4;14,15,26,25;,
  4;15,16,27,26;,
  4;16,17,28,27;,
  4;17,18,29,28;,
  4;18,19,30,29;,
  4;19,20,31,30;,
  4;20,10,21,31;,
  4;21,22,33,32;,
  4;22,23,34,33;,
  4;23,24,35,34;,
  4;24,25,36,35;,
  4;25,26,37,36;,
  4;26,27,38,37;,
  4;27,28,39,38;,
  4;28,29,40,39;,
  4;29,30,41,40;,
  4;30,31,42,41;,
  4;31,21,32,42;,
  4;32,33,44,43;,
  4;33,34,45,44;,
  4;34,35,46,45;,
  4;35,36,47,46;,
  4;36,37,48,47;,
  4;37,38,49,48;,
  4;38,39,50,49;,
  4;39,40,51,50;,
  4;40,41,52,51;,
  4;41,42,53,52;,
  4;42,32,43,53;,
  4;43,44,55,54;,
  4;44,45,56,55;,
  4;45,46,57,56;,
  4;46,47,58,57;,
  4;47,48,59,58;,
  4;48,49,60,59;,
  4;49,50,61,60;,
  4;50,51,62,61;,
  4;51,52,63,62;,
  4;52,53,64,63;,
  4;53,43,54,64;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;;
 }
 MeshTextureCoords {
  108;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.090909;0.000000;,
  0.090909;0.250000;,
  0.000000;0.250000;,
  0.181818;0.000000;,
  0.181818;0.250000;,
  0.272727;0.000000;,
  0.272727;0.250000;,
  0.363636;0.000000;,
  0.363636;0.250000;,
  0.454545;0.000000;,
  0.454545;0.250000;,
  0.545455;0.000000;,
  0.545455;0.250000;,
  0.636364;0.000000;,
  0.636364;0.250000;,
  0.727273;0.000000;,
  0.727273;0.250000;,
  0.818182;0.000000;,
  0.818182;0.250000;,
  0.909091;0.000000;,
  0.909091;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.090909;0.500000;,
  0.000000;0.500000;,
  0.181818;0.500000;,
  0.272727;0.500000;,
  0.363636;0.500000;,
  0.454545;0.500000;,
  0.545455;0.500000;,
  0.636364;0.500000;,
  0.727273;0.500000;,
  0.818182;0.500000;,
  0.909091;0.500000;,
  1.000000;0.500000;,
  0.090909;0.750000;,
  0.000000;0.750000;,
  0.181818;0.750000;,
  0.272727;0.750000;,
  0.363636;0.750000;,
  0.454545;0.750000;,
  0.545455;0.750000;,
  0.636364;0.750000;,
  0.727273;0.750000;,
  0.818182;0.750000;,
  0.909091;0.750000;,
  1.000000;0.750000;,
  0.090909;1.000000;,
  0.000000;1.000000;,
  0.181818;1.000000;,
  0.272727;1.000000;,
  0.363636;1.000000;,
  0.454545;1.000000;,
  0.545455;1.000000;,
  0.636364;1.000000;,
  0.727273;1.000000;,
  0.818182;1.000000;,
  0.909091;1.000000;,
  1.000000;1.000000;,
  0.045455;0.000000;,
  0.136364;0.000000;,
  0.227273;0.000000;,
  0.318182;0.000000;,
  0.409091;0.000000;,
  0.500000;0.000000;,
  0.590909;0.000000;,
  0.681818;0.000000;,
  0.772727;0.000000;,
  0.863636;0.000000;,
  0.954546;0.000000;,
  0.045455;1.000000;,
  0.136364;1.000000;,
  0.227273;1.000000;,
  0.318182;1.000000;,
  0.409091;1.000000;,
  0.500000;1.000000;,
  0.590909;1.000000;,
  0.681818;1.000000;,
  0.772727;1.000000;,
  0.863636;1.000000;,
  0.954546;1.000000;;
 }
 MeshVertexColors {
  108;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;;
 }
}
