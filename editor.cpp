namespace Editor{
	int BSIZE = 12;							//Bricksize or Tilesize
	int BWIDTH = 32;						//Tiles width
	int BHEIGHT = 16;						//Tiled height
	int SWIDTH = 600; 						//Screen width
	int SHEIGHT = 500;  					//Screen height
	int mousex = 0, mousey = 0; 			//Mouse cords
	int lastmousex = 0, lastmousey = 0; 	//Last mouse cords
	int difmousex = 0, difmousey = 0; 		//Difference between actual and last mouse cords
	int tilex = 0, tiley = 0; 				//Actual tile
	double MAXFPS = 120; 					//Max framerate per second
	double FPS = 0; 						//Actual frame per second
};