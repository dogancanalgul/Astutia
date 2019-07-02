#include "Renderer/Renderer.h"
#include "Game/Game.h"

int main(){
	Game game;

	float angle = 0;
	while (!Renderer::renderer.isClosed()){
		glfwPollEvents();

		game.update();

		Renderer::renderer.swapBuffers();
		Renderer::renderer.clear();
	}
	return 0;
}
//Mesh has
//Vertices normals texCoords

//Material has 
//texture maps
//specular shininess

//An  object can have multiple materials thus multiple meshes are needed 
//So A mesh having a material is the most normal one.
//For different faces we must have different meshes then
//Like a cube will have 6 meshes.
//Advice: renderer functions can start with r_
//So cube will have 6 meshes statically
//They also will include the material

//So now TODO:
//MAKE TEXTURE CLASS											done
//ADD MATERIALS TO MESHES (no light so no specular stuff yet)	done
//DIVIDE CUBEMESH TO AN ARRAY WITH 6 MESHES						done
//THEN TRY DRAWING THERE SHOULD BE ONE GOOD LOOKING MESH		done
//CREATE JUST ANOTHER BOX TO SEE IF IT WORKS					done
//STOP FLYING AND HAVE A FLOOR									done
//CREATE COLLISION DETECTION									done
//CREATE GRAVITY												done
//CREATE BOX SELECTION											done
//CREATE SKYBOX													done
//CREATE CHUNKS													
//CREATE FACE CULLING SYSTEM									
//UPDATE CHUNK SYSTEM SO IT CAN GENERATE ALL AROUND YOU			


//(EVERY KIND OF CUBE WILL HAVE DIFFERENT STATIC CUBEMESH)
