#TouhouDanmakufu[Single]
#ScriptVersion[3] //This is required for ph3 scripts
#Title["The embodiment of the gros camtar"]
#Text["help"] 
//Load the default shotsheet
#include "script/default_system/Default_ShotConst.txt"
#include"script/default_system/Default_Effect.txt"

//----------------------------------------------------
//Declaring Global Variables
//The variables declared here can be used throughout the entire script.
//However, the variables declared here are static. 
//(They can be changed, but not by themselves as they are not in the main loop)
//(As execution order cannot be guaranteed, random numbers cannot be used(?))
//----------------------------------------------------
let objEnemy; //Enemy object
let sndSwift1;
let frame = 0; //Counter for timing enemy movements.(Will keep increasing by one in @MainLoop)
let img1 = GetCurrentScriptDirectory() ~ "1.png"; //file path to enemy image
let img2 = GetCurrentScriptDirectory() ~ "2.png"; //file path to enemy image
let flag_satourne = 0;
let flag_grosseboul = 0;
let MAX_LIFE = 3000;
let min_x = GetStgFrameLeft();
let     min_y = GetStgFrameTop();
let     max_x = GetStgFrameWidth();
let     max_y = GetStgFrameHeight();

//----------------------------------------------------
//Enemy movement
//----------------------------------------------------
@Event
{
    alternative(GetEventType())
    case(EV_REQUEST_LIFE)
    {
        //The script asks for the enemy's life
        SetScriptResult(MAX_LIFE); //Setting the enemy's life to 500
    }
    case(EV_REQUEST_SPELL_SCORE)
    {
        SetScriptResult(30000);//スペルカードボーナスを30000に設定
    }
    case(EV_REQUEST_TIMER)
    {
        SetScriptResult(60);//時間制限を60秒に設定
    }
}
@Initialize
{

    //Creating and registering enemy objects
    sndSwift1 = ObjSound_Create();
    objEnemy = ObjEnemy_Create(OBJ_ENEMY_BOSS);
    ObjEnemy_Regist(objEnemy);
    //Setting the enemy's image

    ObjPrim_SetTexture(objEnemy, img1); 
        //Setting the above image file as a texture to the enemy object(objEnemy)
    ObjSprite2D_SetSourceRect(objEnemy, 1, 1, 44, 51); 
        //Setting the rectangle coordinates in the enemy image to use(Left, Top, Right, Bottom).
    ObjSprite2D_SetDestCenter(objEnemy); 
        //Positioning the center of the rectangle(w/texture) at (0, 0) on the stage(top left corner).
    //Moving to the coordinate (cx, 60) in 60 frames
    let cx = GetStgFrameWidth() / 2;
        //defines the variable cx as the horizontal middle of the stage. (Stage width / 2)
    ObjMove_SetDestAtFrame(objEnemy, cx, 60, 60);
    ObjEnemy_SetDamageRate(objEnemy, 5, 5);
    ObjSound_Load(sndSwift1, "resource/sound/switf2.ogg");
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);
    TItemCreateA2(ITEM_POWER, GetPlayerX(), GetPlayerY(), GetPlayerX() + 250 * cos(GetAngleToCenter + 30 + -10), GetPlayerY() + 250*sin(GetAngleToCenter + 30 + -10), 100);

    TMainAttack;
    TFinalize;
}

task TItemCreateA2(type,x,y,gox,goy,score)
{
	let objitem = CreateItemA2(type, x, y, gox, goy, score);
	let speed = 5.7;
	let falling = 0;
	let time = 0;
	let gotoplayer = 0;
	while(!Obj_IsDeleted(objitem))
	{
		if(time > 30)
		{
			if(((ObjMove_GetY(objitem) - GetPlayerY)^2 + (ObjMove_GetX(objitem) - GetPlayerX)^2) < (50^2) && gotoplayer == 0 && GetPlayerState != STATE_DOWN || GetPlayerY < 120 && gotoplayer == 0 && GetPlayerState != STATE_DOWN)
			{
				gotoplayer = 1;
			}
			else if (gotoplayer == 1)
			{
				ObjMove_SetDestAtSpeed(objitem, GetPlayerX, GetPlayerY, speed);
				speed += 0.1;
			}
		}
		time++;
		yield;
	}
	return;
}

let GetAngleToCenter = atan2(GetPlayerY - GetStgFrameHeight/2, GetPlayerX - GetStgFrameWidth/2);

function wait(n){loop(n){yield;}}
function GetCenterX()
{
    return GetStgFrameWidth() / 2;
}
function GetCenterY()
{
    return GetStgFrameHeight() / 2;
}
task TFinalize 
{
    while(ObjEnemy_GetInfo(objEnemy, INFO_LIFE) > 0)
    {
        yield;
    }
    let ex = ObjMove_GetX(objEnemy);
    let ey = ObjMove_GetY(objEnemy);
    TExplosionA(ex, ey, 10, 0.6);
    DeleteShotAll(TYPE_ALL, TYPE_ITEM);//敵弾を全て削除    
    Obj_Delete(objEnemy);
    SetAutoDeleteObject(true);
    CloseScript(GetOwnScriptID());
    return;
}

/*task homing_shot
{
    let ex = ObjMove_GetX(objEnemy);
    let ey = ObjMove_GetY(objEnemy);
    let shot = CreateShotA1(ex, ey, 0, GetAngleToPlayer(objEnemy), DS_BALL_L_RED, 0);
    
    ObjMove_SetAcceleration(shot, 0.01);
    ObjMove_SetMaxSpeed(shot, 100);
    while (ObjEnemy_GetInfo(objEnemy, INFO_LIFE) > 0)
    {   
        let px = GetPlayerX();
        let py = GetPlayerY();
        let pax = GetAngleToPlayer(shot);
        ObjMove_SetAngle(shot, pax);
        yield;
        let i = 0;
        while (1)
        {

            let sx = ObjMove_GetX(shot);
            let sy = ObjMove_GetY(shot);
            if (sx < min_x || sx > max_x || sy < min_y || sy > max_y || i == 60)
            {
                break;
            }
            yield;
            i++;
        }
        ObjMove_SetSpeed(shot, 0.1)
    }
}*/

task TMedShot(i, sx, sy)
{
    let med_shot = CreateShotA1(sx, sy, 3, i - 180 , DS_BALL_L_BLUE, 0);
    
    while (!Obj_IsDeleted(med_shot))
    {
        let sx = ObjMove_GetX(med_shot);
        let sy = ObjMove_GetY(med_shot);
        if (sx > max_x)
        {
            Obj_Delete(med_shot);
            ascent (i in 0 .. 18)
            {
                CreateShotA1(sx, sy, 2, i * 10 + 90 + 0, DS_BALL_SS_BLUE, 5);
            }
        }
        if (sx < min_x - 30)
        {
            Obj_Delete(med_shot);
            ascent (i in 0 .. 18)
            {
                CreateShotA1(sx, sy, 2, i * 10 - 90 + 0, DS_BALL_SS_BLUE, 5);
            }
        }
        if (sy < min_y - 30)
        {
            Obj_Delete(med_shot);
            ascent (i in 0 .. 18)
            {
                CreateShotA1(sx, sy, 2, i * 10 + 0, DS_BALL_SS_BLUE, 5);
            }
        }
        if (sy > max_y)
        {
            Obj_Delete(med_shot);
            ascent (i in 0 .. 18)
            {
                CreateShotA1(sx, sy, 2, i * 10 - 180 + 0, DS_BALL_SS_BLUE, 5);
            }
        }
        yield;
    }
}

task TMainAttack
{
    let j = 0;

    wait(60);
    while (!Obj_IsDeleted(objEnemy))
    {
        ascent (i in 0 .. 6)
        {
            TMedShot(i * 60 + j * 10, ObjMove_GetX(objEnemy), ObjMove_GetY(objEnemy));
            TMedShot(i * 60 - j * 10, ObjMove_GetX(objEnemy), ObjMove_GetY(objEnemy));
        }
        wait(300);
        j++;
    }
}

@MainLoop
{
        ObjEnemy_SetIntersectionCircleToShot(objEnemy, ObjMove_GetX(objEnemy), ObjMove_GetY(objEnemy), 32); 
    ObjEnemy_SetIntersectionCircleToPlayer(objEnemy, ObjMove_GetX(objEnemy), ObjMove_GetY(objEnemy), 24);
    frame++;
    yield;
}