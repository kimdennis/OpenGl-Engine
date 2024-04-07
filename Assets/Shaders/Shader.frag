
#version 410 core

layout(location = 0) in vec3 outColor;


layout(location = 0) out vec4 color;


void main(){

   float borderThickness = 0.03;

   //if texcoords are in the border thickness area, return light blue color (0,0.5,1,1), otherwise, make a faded color
   if ((outColor.x > 0.0+borderThickness && outColor.x < 1.0-borderThickness) && (outColor.y > 0.0+borderThickness && outColor.y < 1.0-borderThickness))
       color = vec4(0.5,0,0.2+outColor.x,1);
   else
       color = vec4(0,0.5,1,1);

  color.a =1;
  color.rgb*=0.75;
}
