/*
	Scalable Building Simulator - Core
	The Skyscraper Project - Version 1.1 Alpha
	Copyright �2005-2006 Ryan Thoryk
	http://www.tliquest.net/skyscraper
	http://sourceforge.net/projects/skyscraper
	Contact - ryan@tliquest.net

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "globals.h"

//#include "csutil/ref.h"

//global functions
bool IsEven(int Number);
float AutoSize(float n1, float n2, bool iswidth);
static bool SBSEventHandler(iEvent& Event);
void Cleanup();

struct iEngine;
struct iSector;
struct iView;
struct iFont;
struct iFile;
struct iKeyboardDriver;
struct iImageLoader;
struct iLoaderPlugin;
struct iMeshWrapper;
struct iConsoleOutput;
struct iVirtualClock;
struct iObjectRegistry;
struct iGraphics3D;
struct iGraphics2D;
struct iLoader;
struct iVFS;
struct iEvent;
class DemoSequenceManager;
class csTransform;

struct sbsVector3
{
	float x;
	float y;
	float z;
};

class SBS
{
public:

    //Engine data
	csRef<iEngine> engine;
	csRef<iLoader> loader;
	csRef<iGraphics3D> g3d;
	csRef<iGraphics2D> g2d;
	csRef<iKeyboardDriver> kbd;
	csRef<iVirtualClock> vc;
	csRef<iView> view;
	csRef<iLight> light;
	csRef<iConsoleOutput> console;
	csRef<iFont> font;
	csRef<iVFS> vfs;
	csRef<iImageIO> imageio;
	csRef<iCommandLineParser> cmdline;
	csRef<iGeneralMeshState> gmSingle;
	csRef<iStringSet> strings;
	
	iMaterialWrapper* material;
	iLightList* ll;
	iSector* area;

	csTicks elapsed_time;

	//Building information
	csString BuildingName;
	csString BuildingDesigner;
	csString BuildingLocation;
	csString BuildingDescription;
	csString BuildingVersion;

	//Internal data
    float Gravity; //gravity variable for physics algorithms
    bool IsRunning; //is sim engine running?
    int ElevatorShafts; //number of elevator shafts
	int TotalFloors; //number of above-ground floors including 0
	int Basements; //number of basement floors
	int Elevators; //number of elevators
	int PipeShafts; //number of pipe shafts
	int StairsNum; //number of stairwells
	csArray<Floor*> FloorArray; //pointer array to floor objects
	csArray<Elevator*> ElevatorArray; //pointer array to elevator objects
	bool RenderOnly; //skip sim processing and only render graphics
    bool InputOnly; //skip sim processing and only run input and rendering code
    bool IsFalling; //make user fall
	float FallRate; //falling rate
    bool InStairwell; //true if user is in a stairwell
	bool InElevator; //true is user is in an elevator
    int ElevatorNumber; //number of currently selected elevator
	bool FrameLimiter; //frame limiter toggle
    int FrameRate; //max frame rate
	float FPSModifier; //modification value for FPS changes
	bool FrameSync; //synchronize movement to frame rate
	bool EnableCollisions; //turns collisions on/off
	float HorizScale; //horizontal X/Z scaling multiplier (in feet). Normally is 1
	float Feet; //feet scale value
	csStringArray UserVariable;

	//File I/O
	csString BuildingFile;
	csArray<csString> BuildingData;
	long FileLines;

	//public functions
	SBS();
	~SBS();
	void Report (const char* msg, ...);
	bool ReportError (const char* msg, ...);
	void Wait(long Milliseconds);
	void SlowToFPS(long FrameRate);
	bool LoadTexture(const char *name, const char *filename);
	bool Initialize(int argc, const char* const argv[], const char *windowtitle);
 	void Start();
	void AddLight(const char *name, float x, float y, float z, float radius, float r, float g, float b);
	void AddWallMain(csRef<iThingFactoryState> dest, const char *texture, float x1, float z1, float x2, float z2, float height_in1, float height_in2, float altitude1, float altitude2, float tw, float th);
	void AddFloorMain(csRef<iThingFactoryState> dest, const char *texture, float x1, float z1, float x2, float z2, float altitude, float tw, float th);
	bool HandleEvent(iEvent& Event);
	void SetupFrame();
	void FinishFrame();
	void CreateWallBox2(csRef<iThingFactoryState> dest, const char *texture, float CenterX, float CenterZ, float WidthX, float LengthZ, float height_in, float voffset, float tw, float th);
	void InitMeshes();

	//file loader functions
	int LoadBuilding(const char * filename);
	int LoadDataFile(const char * filename);
	long GetLines(const char * filename);
	bool FileExists(const char * filename);

	//Meshes
	csRef<iMeshWrapper> Buildings; //building mesh
		csRef<iMeshObject> Buildings_object;
		csRef<iMeshObjectFactory> Buildings_factory;
		csRef<iThingFactoryState> Buildings_state;

	csRef<iMeshWrapper> External; //external mesh
		csRef<iMeshObject> External_object;
		csRef<iMeshObjectFactory> External_factory;
		csRef<iThingFactoryState> External_state;

	csRef<iMeshWrapper> Landscape; //landscape mesh
		csRef<iMeshObject> Landscape_object;
		csRef<iMeshObjectFactory> Landscape_factory;
		csRef<iThingFactoryState> Landscape_state;

	csRef<iMeshWrapper> ColumnFrame; //column frame mesh
		csRef<iMeshObject> ColumnFrame_object;
		csRef<iMeshObjectFactory> ColumnFrame_factory;
		csRef<iThingFactoryState> ColumnFrame_state;

private:

	csEventID FocusGained;
	csEventID FocusLost;
	csEventID Process;
	csEventID FinalProcess;
	csEventID KeyboardDown;

	//private functions
	void PrintBanner();
};
