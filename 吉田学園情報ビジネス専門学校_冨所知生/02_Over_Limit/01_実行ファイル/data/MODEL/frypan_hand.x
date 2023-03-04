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
 24;
 -3.20681;0.25531;-0.49000;,
 3.19719;0.29080;-0.49000;,
 3.20039;0.05748;-0.49000;,
 -3.20360;0.02198;-0.49000;,
 3.20360;-0.17585;-0.49000;,
 -3.20039;-0.21134;-0.49000;,
 3.20681;-0.40917;-0.49000;,
 -3.19719;-0.44467;-0.49000;,
 3.19719;0.29080;0.00000;,
 3.20039;0.05748;0.00000;,
 3.19719;0.29080;0.49000;,
 3.20039;0.05748;0.49000;,
 3.20360;-0.17585;-0.00000;,
 3.20360;-0.17585;0.49000;,
 3.20681;-0.40917;-0.00000;,
 3.20681;-0.40917;0.49000;,
 -3.20681;0.25531;0.49000;,
 -3.20360;0.02198;0.49000;,
 -3.20039;-0.21134;0.49000;,
 -3.19719;-0.44467;0.49000;,
 -3.20681;0.25531;0.00000;,
 -3.20360;0.02198;0.00000;,
 -3.20039;-0.21134;0.00000;,
 -3.19719;-0.44467;0.00000;;
 
 22;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;8,10,11,9;,
 4;2,9,12,4;,
 4;9,11,13,12;,
 4;4,12,14,6;,
 4;12,13,15,14;,
 4;10,16,17,11;,
 4;11,17,18,13;,
 4;13,18,19,15;,
 4;16,20,21,17;,
 4;20,0,3,21;,
 4;17,21,22,18;,
 4;21,3,5,22;,
 4;18,22,23,19;,
 4;22,5,7,23;,
 4;16,10,8,20;,
 4;20,8,1,0;,
 4;23,14,15,19;,
 4;7,6,14,23;;
 
 MeshMaterialList {
  2;
  22;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.373600;0.373600;0.373600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.564706;0.426667;0.207059;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  18;
  0.000000;0.000000;-1.000000;,
  0.999906;0.013745;0.000000;,
  0.999906;0.013744;0.000000;,
  0.999906;0.013739;0.000000;,
  0.999906;0.013736;0.000000;,
  0.999906;0.013744;0.000000;,
  0.999906;0.013736;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.999906;-0.013732;0.000000;,
  -0.999906;-0.013739;0.000000;,
  -0.999906;-0.013741;0.000000;,
  -0.999906;-0.013736;0.000000;,
  -0.999906;-0.013739;0.000000;,
  -0.999906;-0.013741;0.000000;,
  -0.005543;0.999985;0.000000;,
  -0.005543;0.999985;0.000000;,
  0.005543;-0.999985;-0.000000;,
  0.005543;-0.999985;-0.000000;;
  22;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,2,5;,
  4;1,1,5,2;,
  4;5,2,3,3;,
  4;2,5,3,3;,
  4;3,3,4,6;,
  4;3,3,6,4;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;8,8,9,12;,
  4;8,8,12,9;,
  4;12,9,10,13;,
  4;9,12,13,10;,
  4;13,10,11,11;,
  4;10,13,11,11;,
  4;14,14,15,15;,
  4;15,15,14,14;,
  4;16,16,17,17;,
  4;17,17,16,16;;
 }
}
