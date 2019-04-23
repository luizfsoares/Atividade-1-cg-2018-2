#include <iostream>
#include <glm/glm.hpp>
#include <mygl.h>
#include <math.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <bits/stdc++.h>
#include <glm/mat4x4.hpp>
#include <definitions.h>
#include <vector>
#include <loader.h>





void pipeline(float angulo){

   //model  Objeto ---> Universo
   

    glm::mat4x4 mTranslacao = glm::mat4x4(1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0, 0, 1);

    glm::mat4x4 mEscala = glm::mat4x4(1, 0, 0, 0,
                                      0, -1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1); 

        float angX = 0.0;
        float angY = angulo;
        float angZ = 0.0;

    glm::mat4x4 mRotacaoX = glm::mat4x4(1, 0, 0, 0,
                                        0, cos(angX), sin(angX), 0,
                                        0, -sin(angX), cos(angX), 0,
                                        0, 0, 0, 1);

    glm::mat4x4 mRotacaoY = glm::mat4x4(cos(angY), 0, -sin(angY), 0,
                                      0, 1, 0, 0,
                                      sin(angY), 0, cos(angY), 0,
                                      0, 0, 0, 1);

    glm::mat4x4 mRotacaoZ = glm::mat4x4(cos(angZ), sin(angZ), 0, 0,
                                        -sin(angZ), cos(angZ), 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1);

    glm::mat4x4 mRotacao = mRotacaoX*mRotacaoY*mRotacaoZ;

    glm::mat4x4 mModel = mTranslacao * mEscala * mRotacao;                                 


    //view   Universo ---> Câmera

    glm::vec3 lookCam = glm::vec3(0,0,0);
    glm::vec3 posCam = glm::vec3(0,0,3);
    glm::vec3 upCam = glm::vec3(0,1,0);

    glm::vec3 dCam = lookCam - posCam;
    
    
    glm::vec3 zCam = -normalize(dCam);
    glm::vec3 xCam = normalize(cross(upCam, zCam));
    glm::vec3 yCam = cross(zCam, xCam);

    glm::mat4x4 Bt = glm::mat4x4(xCam[0], yCam[0], zCam[0],0,
                                 xCam[1], yCam[1], zCam[1],0,
                                 xCam[2], yCam[2], zCam[2],0,
                                 0,0,0,1 );

    glm::mat4x4 T =  glm::mat4x4(1, 0, 0, 0,
                                 0, 1, 0, 0,
                                 0, 0, 1, 0,
                                 -dCam[0], -dCam[1], -dCam[2], 1);

    glm::mat4x4 mView = Bt*T;

    //projeção   Câmera ---> Projetivo

    int d = 1;

    glm::mat4x4 mProjecao = glm::mat4x4(1,0,0,0,
                                        0,1,0,0,
                                        0,0,1,-(1/d),
                                        0,0,d,0);

    //viewport Projetivo/Canônico ---> Tela (Divisão por w ocorre após multiplicação de matrizes
    // para facilitar a implementação)

    int w = 512;
    int h = 512;

    glm::mat4x4 mTranslacaoTela = glm::mat4x4(1,0,0,0,
                                           0,1,0,0,
                                           0,0,1,0,
                                           (w-1)/2, (h-1)/2, 0, 1);


    glm::mat4x4 mEscalaTela = glm::mat4x4(w/2, 0, 0, 0,
                                          0, h/2, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0, 0, 1);

    glm::mat4x4 mInverteTela = glm::mat4x4(1, 0, 0, 0,
                                          0, -1, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0, 0, 1);

    glm::mat4x4 mViewPort = mTranslacaoTela * mEscalaTela * mInverteTela;

    glm::mat4x4 mPipeline =  mViewPort * mProjecao * mView * mModel; //Matriz Pipeline criada



    //Desenho
    
    std::vector<glm::vec4> vertices = carregandoModelo("monkey.obj");

    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] = mPipeline * vertices[i];
        vertices[i] = vertices[i] / vertices[i].w;
    }

    for (int i = 0; i < vertices.size(); i += 3)
    {

        DrawTriangle((int)vertices[i].x, (int)vertices[i].y, white,
                     (int)vertices[i + 1].x, (int)vertices[i + 1].y, white,
                     (int)vertices[i + 2].x, (int)vertices[i + 2].y, white);

    }

    //teste 1 movimentando câmera olhando para um triângulo


}