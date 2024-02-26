
#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"

#define DO_NOT_RUN 1984
//Sets up Variables
int displayMode = 0;
int selectedProgram = DO_NOT_RUN;
int autoType = 0;
int selectedProfile = 0;
int selectedGIF =0;
int selectedDebugOption=0;
char kPChar[50];
char kIChar[50];
char kDChar[50];
bool btnmkPFirst=true;
bool btnmkIFirst=true;
bool btnmkDFirst=true;
//Sets up which programs to select from
const char* GIFFilePaths[] = {"/usd/Sylvie.gif","/usd/Catapult.gif","/usd/Alliance.gif","/usd/Glitch.gif","/usd/Lightning.gif","/usd/Rumble.gif"};
void (*redScripts[])() = {rightRedOneAuton, rightRedTwoAuton, elimMatchRightAuton, disabledAuton, leftRedOneAuton, leftRedTwoAuton,elimMatchLeftAuton};
void (*blueScripts[])() = {rightBlueOneAuton, rightBlueTwoAuton, elimMatchRightAuton, disabledAuton, leftBlueOneAuton, leftBlueTwoAuton,elimMatchLeftAuton};
void (*skillsScripts[])() = {pSkills,dSkills};



//Creates the Objects
//Creates Screens
lv_obj_t* autonScreen = lv_obj_create(NULL, NULL); 
lv_obj_t* skillsScreen = lv_obj_create(NULL,NULL);
lv_obj_t* debugScreen = lv_obj_create(NULL, NULL);
lv_obj_t* profileScreen = lv_obj_create(NULL,NULL);
lv_obj_t* visualScreen = lv_obj_create(NULL,NULL);
lv_obj_t* pidScreen = lv_obj_create(NULL,NULL);
lv_obj_t* pidChartScreen = lv_obj_create(NULL,NULL);

//Creates drowdown menus
lv_obj_t* ddlColorSelection = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlAutonSelector = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlSkillsSelector = lv_ddlist_create(skillsScreen, NULL);
lv_obj_t* ddlProfileSelector = lv_ddlist_create(profileScreen, NULL);
lv_obj_t* ddlDebugOptionSelector = lv_ddlist_create(debugScreen,NULL);
lv_obj_t* ddlGIF = lv_ddlist_create(visualScreen,NULL);
lv_obj_t* ddlAuton = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlSkills = lv_ddlist_create(skillsScreen, NULL);
lv_obj_t* ddlProfile = lv_ddlist_create(profileScreen, NULL);
lv_obj_t* ddlDebug = lv_ddlist_create(debugScreen, NULL);
lv_obj_t* ddlVision = lv_ddlist_create(visualScreen, NULL);

//Creates text areas
lv_obj_t* kPTextArea = lv_ta_create(pidScreen,NULL);
lv_obj_t* kITextArea = lv_ta_create(pidScreen,NULL);
lv_obj_t* kDTextArea = lv_ta_create(pidScreen,NULL);

//Creates Button Matrices
lv_obj_t* btnmkP = lv_btnm_create(pidScreen,NULL);
lv_obj_t* btnmkI = lv_btnm_create(pidScreen,NULL);
lv_obj_t* btnmkD = lv_btnm_create(pidScreen,NULL);

//the action for when using the main dropdownlist
static lv_res_t ddlistMenuingAction(lv_obj_t *ddlist){
    // Gets the selected index of the dropdown list
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch (selected_index){
    case 0:
        // if first option selected loads auton screen and updates the ddl on the auton screen.
        lv_scr_load(autonScreen);
        lv_ddlist_set_selected(ddlAuton, 0);
        break;
    case 1:
        // if second option selected loads skills screen and updates the ddl on the skills screen.
        lv_scr_load(skillsScreen);
        lv_ddlist_set_selected(ddlSkills, 1);
        break;
    case 2:
        // if third option selected loads profile screen and updates the ddl on the profile screen.
        lv_scr_load(profileScreen);
        lv_ddlist_set_selected(ddlProfile, 2);
        break;
    case 3:
    // if fourth option selected loads debug screen and updates the ddl on the debug screen.
        lv_scr_load(debugScreen);
        lv_ddlist_set_selected(ddlDebug, 3);
        break;
    case 4:
    // if fifth option selected loads Gif screen and updates the ddl on the gif screen.
        lv_scr_load(visualScreen);
        lv_ddlist_set_selected(ddlVision,4);
        break;
    default:
        break;
    }
    return LV_RES_OK; 
}
static lv_res_t ddlistColorSelectionAction(lv_obj_t *ddlist){
    // Gets the selected index of the dropdown list
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch (selected_index){
    case 0:
        break;
    case 1:
        //If the second option is selected sets auto type to blue
	    autoType = AUTONOMOUS_BLUE;
        break;
    case 2:
        //If the third option is selected sets auto type to red
	    autoType = AUTONOMOUS_RED;
        break;
    default:
        break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistAutonSelectorAction(lv_obj_t *ddlist){
    // Gets the selected index of the dropdown list
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch (selected_index){
    case 0:
        //If the first option is selected sets auton to disabled
        selectedProgram = 3;    
        break;
    case 1:
        //If the second option is selected sets auton to rightOneAuton of selected color
        selectedProgram = 0;
        break;
    case 2:
        //If the third option is selected sets auton to rightTwoAuton of selected color
        selectedProgram = 1;
        break;
    case 3:
        //If the fourth option is selected sets auton to rightElimAuton of selected color
        selectedProgram = 2;
        break;
    case 4:
        //If the fifth option is selected sets auton to disabled
        selectedProgram = 3;
        break;
    case 5:
        //If the sixth option is selected sets auton to leftOneAuton of selected color
        selectedProgram = 4;
        break;
    case 6:
        //If the seventh option is selected sets auton to leftTwoAuton of selected color
        selectedProgram = 5;
        break;
    case 7:
        //If the seventh option is selected sets auton to leftTwoAuton of selected color
        selectedProgram = 6;
        break;
    default:
       //For the else statement sets auton to disabled
        selectedProgram = 3;
        break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistSkillSelectorAction(lv_obj_t* ddlist) {
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch(selected_index){
    case 0:
        break;
    case 1:
        //If the second option is selected sets auto type to skills, and selected program to programming skills
        autoType = AUTONOMOUS_SKILLS;
        selectedProgram=0;
        break;
    case 2:
        //If the second option is selected sets auto type to skills, and selected program to driver skills
        autoType = AUTONOMOUS_SKILLS;
        selectedProgram=1;
        break;
    default:
        break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistProfileSelectorAction(lv_obj_t* ddlist) {
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch(selected_index){
        case 0:
            break;
        case 1:
            //If the second option is selected, it selectes the first profile
            selectedProfile = 0;
            break;
        case 2:
            //If the third option is selected, it selectes the second profile
            selectedProfile=1;
            break;
        default:
            break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistDebugOptionSelectorAction (lv_obj_t* ddlist) {
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch(selected_index){
        case 0: 
            selectedDebugOption=0;
            break;
        case 1:
            selectedDebugOption=1;
            break;
        case 2:
            selectedDebugOption=2;
            break;
    }
}

static lv_res_t ddlistGIFSelectorAction(lv_obj_t* ddlist){
    uint16_t selected_index =lv_ddlist_get_selected(ddlist);
    switch(selected_index){
        case 0:
            break;
        case 1:
            //If the second option is selected, it selectes the first gif
            selectedGIF=0;
            break;
        case 2:
            //If the third option is selected, it selectes the second gif
            selectedGIF=1;
            break;
        case 3:
            //If the fourth option is selected, it selectes the third gif
            selectedGIF=2;
            break;
        case 4:
            //If the fifth option is selected, it selectes the fourth gif
            selectedGIF=3;
            break;
        case 5:
            //If the sixth option is selected, it selectes the fifth gif
            selectedGIF=4;
            break;
        case 6:
            //If the seventh option is selected, it selectes the sixth gif
            selectedGIF=5;
        default:
            break;
        
    }
    return LV_RES_OK;
}

static lv_res_t btnmPIDAction(lv_obj_t * btnm, const char* txt) {  
    if (btnm==btnmkP){
        if (btnmkPFirst){
            lv_ta_set_text(kPTextArea,"");
            btnmkPFirst=false;
        } 
        if (txt=="Back"){
            lv_ta_del_char(kPTextArea);
        }
        else if (txt=="Enter"){
            kP=atof(lv_ta_get_text(kPTextArea));
        }
        else{
            lv_ta_add_text(kPTextArea, txt);
        }
    }
    else if (btnm==btnmkI){
        if (btnmkIFirst){
            lv_ta_set_text(kITextArea,"");
            btnmkIFirst=false;
        }
        if(txt=="Back"){
            lv_ta_del_char(kITextArea);
        }
        else if (txt=="Enter"){
            kI=atof(lv_ta_get_text(kITextArea));
        }
        else{
            lv_ta_add_text(kITextArea,txt);
        }
    }
    else if (btnm==btnmkD){
        if (btnmkDFirst){
            lv_ta_set_text(kDTextArea,"");
            btnmkDFirst=false;
        }
        if(txt=="Back"){
            lv_ta_del_char(kDTextArea);
        }
        else if (txt=="Enter"){
            kD=atof(lv_ta_get_text(kDTextArea));
        }
        else{
            lv_ta_add_text(kDTextArea,txt);
        }
    }

    return LV_RES_OK; 
}


//Main Code
void MainLVGL(void)
{
    //sets the style for a screen, with a black and gray gradiant
    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain);
    style.body.main_color = LV_COLOR_BLACK;
    style.body.grad_color = LV_COLOR_HEX(0x3A3B3C);
    

    //gives the style to the auton screen
    lv_obj_set_style(autonScreen,&style);

    //sets the options for ddlAutonSelector
    lv_ddlist_set_options(ddlAutonSelector, " \n" "Right AWP\n" "Right No Bar\n" "Right Elim\n" "Disabled\n" "Left AWP\n" "Left No Bar\n" "Anti-Auton\n");
    //links ddlAutonSelector to the action, ddlistAutonSelectorAction to give the ddl logic.
    lv_ddlist_set_action(ddlAutonSelector, ddlistAutonSelectorAction);
    //sets a fixed height for ddlAutonSelector so it won't go off screen
    lv_ddlist_set_fix_height(ddlAutonSelector, 150);
    //sets the mode of ddlAutonSelector so you can swipe through the options
    lv_ddlist_set_sb_mode(ddlAutonSelector, LV_SB_MODE_DRAG);
    //aligns ddlAutonSelector on the screen
    lv_obj_align(ddlAutonSelector, NULL, LV_ALIGN_IN_LEFT_MID, 95, -20);

    //sets the options for ddlColorSelection
    lv_ddlist_set_options(ddlColorSelection, " \n" "Blue\n" "Red\n");
    //links ddlColorSelection to the action, ddlistColorSelectionAction to give the ddl logic
    lv_ddlist_set_action(ddlColorSelection, ddlistColorSelectionAction);
    //aligns ddlColorSelection on the screen
    lv_obj_align(ddlColorSelection, NULL, LV_ALIGN_IN_LEFT_MID, 5, -20);

    //sets the options for ddlAuton
    lv_ddlist_set_options(ddlAuton, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    //links ddlAuton to the action, ddlistMenuingAction to give the ddl logic
    lv_ddlist_set_action(ddlAuton, ddlistMenuingAction);
    //sets ddlAuton to option 1
    lv_ddlist_set_selected(ddlAuton, 0);
    //aligns ddlAuton on the screen
    lv_obj_align(ddlAuton, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

    //creates a lvgl object(gifObjAuton) for the auton screen for a gif
    lv_obj_t* gifObjAuton = lv_obj_create(autonScreen, NULL);
    //sets the size of the object(gifObjAuton)
    lv_obj_set_size(gifObjAuton, 480, 240);
    //makes gifObjAuton transparent
    lv_obj_set_style(gifObjAuton, &lv_style_transp); 
    //aligns gifObjAuton on the screen
    lv_obj_align(gifObjAuton, NULL, LV_ALIGN_IN_RIGHT_MID, 300,60);
    //creates a Gif object in the object gifObjAuton
    static Gif gifAuton("/usd/SPSIntro.gif", gifObjAuton);

    
    //gives the style to the skills screen
    lv_obj_set_style(skillsScreen, &style);

    //sets the options for ddlSkills
    lv_ddlist_set_options(ddlSkills, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    //links ddlSkills to the action, ddlistMenuingAction to give the ddl logic
    lv_ddlist_set_action(ddlSkills, ddlistMenuingAction);
    //aligns ddlSkills on the screen
    lv_obj_align(ddlSkills, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

    //sets the options for ddlSkillsSelector
    lv_ddlist_set_options(ddlSkillsSelector, " \n" "Programming Skills\n" "Driver Skills\n");
    //links ddlSkills to the action, ddlistSkillSelectorAction to give the ddl logic
    lv_ddlist_set_action(ddlSkillsSelector, ddlistSkillSelectorAction);
    //aligns ddlSkillsSelector on the screen
    lv_obj_align(ddlSkillsSelector, NULL, LV_ALIGN_IN_LEFT_MID, 5,-20);


    //gives the style to the profile screen
    lv_obj_set_style(profileScreen, &style);

    //sets the options for ddlProfile
    lv_ddlist_set_options(ddlProfile, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    //links ddlProfile to the action, ddlistMenuingAction to give the ddl logic
    lv_ddlist_set_action(ddlProfile, ddlistMenuingAction);
    //aligns ddlProfile on the screen
    lv_obj_align(ddlProfile, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

    //sets the options for ddlProfileSelector
    lv_ddlist_set_options(ddlProfileSelector, " \n" "Gaston\n" "Patrick\n");
    //links ddlProfileSelector to the action, ddlistProfileSelectorAction to give the ddl logic
    lv_ddlist_set_action(ddlProfileSelector, ddlistProfileSelectorAction);
    //aligns ddlProfileSelector on the screen
    lv_obj_align(ddlProfileSelector, NULL, LV_ALIGN_IN_LEFT_MID, 5, -20);


    //gives the style to the debug screen
    lv_obj_set_style(debugScreen, &style);

    //sets the options for ddlDebug
    lv_ddlist_set_options(ddlDebug, "Auton\n" "Skills\n" "Profile\n" "Debug\n" "GIFs\n");
    //links ddlDebug to the action, ddlistMenuingAction to give the ddl logic
    lv_ddlist_set_action(ddlDebug, ddlistMenuingAction);
    //aligns ddlDebug on the screen
    lv_obj_align(ddlDebug, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

    //sets the options for ddlDebugSelector
    lv_ddlist_set_options(ddlDebugOptionSelector, "\n" "PID Info\n" "Motor Info\n");
    //links ddlDebugSelector to the action ddlistDebugSelectorAction to give the ddl logic
    lv_ddlist_set_action(ddlDebugOptionSelector, ddlistDebugOptionSelectorAction);
    //aligns ddlDebugSelector
    lv_obj_align(ddlDebugOptionSelector, NULL, LV_ALIGN_IN_LEFT_MID, 5,-20);
    
    
    //gives the style to the visual screen
    lv_obj_set_style(visualScreen, &style);

    //sets the options for ddlVision
    lv_ddlist_set_options(ddlVision, "Auton\n" "Skills\n" "Profile\n" "Debug\n" "GIFs\n");
    //links ddlVision to the action, ddlistMenuingAction to give the ddl logic
    lv_ddlist_set_action(ddlVision, ddlistMenuingAction);
    //aligns ddlVision on the screen
    lv_obj_align(ddlVision, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

    //sets the options for ddlGIF
    lv_ddlist_set_options(ddlGIF, " \n" "Sylvie\n" "Catapult\n" "Alliance\n" "Glitch\n" "Lightning\n" "Rumble\n");
    //links ddlGIF to the action, ddlistGIFSelectorAction to give the ddl logic
    lv_ddlist_set_action(ddlGIF, ddlistGIFSelectorAction);
    //sets a fixed height for ddlGIF so it won't go off screen
    lv_ddlist_set_fix_height(ddlGIF, 150);
    //sets the mode of ddlGIF so you can swipe through the options
    lv_ddlist_set_sb_mode(ddlGIF, LV_SB_MODE_DRAG);
    //aligns ddlGIF on the screen
    lv_obj_align(ddlGIF, NULL, LV_ALIGN_IN_LEFT_MID, 5, -20);
    

    // Load the auton screen
    lv_scr_load(autonScreen);
}


//Increments the timer
void display(void) {
	lv_task_handler();
	lv_tick_inc(5);
}


//Code to run the right auton based off the checkboxes
void runSelectedAuto(void) {

    //checks if an auton was selected
	if (selectedProgram == DO_NOT_RUN) {
		return;
	}

    //if so uses a switch case depending on the autotype
	switch (autoType) {
		case AUTONOMOUS_RED:
			printf("LEFT\n");
            //runs the function/program in the array redScripts of the index selectedProgram
			redScripts[selectedProgram]();
			break;
		case AUTONOMOUS_BLUE:
			printf("RIGHT\n");
            //runs the function/program in the array blueScripts of the index selectedProgram
			blueScripts[selectedProgram]();
			break;
		case AUTONOMOUS_SKILLS:
			printf("SKILLS\n");
            //runs the function/program in the array skillsScripts of the index selectedProgram
			skillsScripts[selectedProgram]();
			break;
	}
}


//Creates a function to display a GIF
void runSelectedGIF(void) {
    //Creates a screen to display the GIF
    lv_obj_t* GIFScreen = lv_obj_create(NULL,NULL);
    //Creates a container object on the screen to display the GIF
    lv_obj_t* gifObjMain = lv_obj_create(GIFScreen, NULL);
    //Sets the size of the container object
    lv_obj_set_size(gifObjMain, 480, 240);
    //Makes the container object transparent
    lv_obj_set_style(gifObjMain, &lv_style_transp); 
    //Aligns the container object
    lv_obj_align(gifObjMain, NULL, LV_ALIGN_IN_RIGHT_MID, 0,0);
    //Creates on GIF object on the container object, the selected GIF is pulled from the array GIFFilePaths, and the index selectedGIF, to select a GIF
    static Gif gifMain(GIFFilePaths[selectedGIF], gifObjMain);
    //Loads the screen
    lv_scr_load(GIFScreen);
}

void PIDScreen(void){

    static lv_style_t style_bg;
    style_bg.body.main_color = LV_COLOR_BLACK;
    style_bg.body.padding.hor = 0;
    style_bg.body.padding.ver = 0;
    style_bg.body.padding.inner = 0;

    /*Create 2 button styles*/
    static lv_style_t style_btn_rel;
    static lv_style_t style_btn_pr;
    lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
    style_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
    style_btn_rel.body.grad_color = LV_COLOR_BLACK;
    style_btn_rel.body.border.color = LV_COLOR_SILVER;
    style_btn_rel.body.border.width = 1;
    style_btn_rel.body.border.opa = LV_OPA_50;


    lv_ta_set_cursor_type(kPTextArea, LV_CURSOR_HIDDEN);
    lv_ta_set_cursor_type(kITextArea,LV_CURSOR_HIDDEN);
    lv_ta_set_cursor_type(kDTextArea,LV_CURSOR_HIDDEN);
    lv_obj_set_size(kPTextArea,150,50);
    lv_obj_set_size(kITextArea,150,50);
    lv_obj_set_size(kDTextArea,150,50);
    sprintf(kPChar,"kP: %f",kP);
    sprintf(kIChar,"kI: %f",kI);
    sprintf(kDChar,"kD: %f",kD);
    lv_ta_set_text(kPTextArea,kPChar);
    lv_ta_set_text(kITextArea,kIChar);
    lv_ta_set_text(kDTextArea,kDChar);
    lv_obj_align(kITextArea,NULL,LV_ALIGN_IN_TOP_MID,0,0);
    lv_obj_align(kDTextArea,NULL,LV_ALIGN_IN_TOP_RIGHT,0,0);


    static const char * numPad[] = {"1", "2", "3", "\n",
                                      "4", "5", "6", "\n",
                                      "7", "8", "9", "\n",
                                      "Back", "0", "Enter", "\n",
                                      " ", ".", " ", ""
                                     };
    lv_obj_set_size(btnmkP, 150, 150);
    lv_obj_set_size(btnmkI,150,150);
    lv_obj_set_size(btnmkD,150,150);
    lv_btnm_set_map(btnmkP,numPad);
    lv_btnm_set_map(btnmkI,numPad);
    lv_btnm_set_map(btnmkD,numPad);
    lv_btnm_set_style(btnmkP, LV_BTNM_STYLE_BG, &style_bg);
    lv_btnm_set_style(btnmkP, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
    lv_btnm_set_style(btnmkI, LV_BTNM_STYLE_BG, &style_bg);
    lv_btnm_set_style(btnmkI, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
    lv_btnm_set_style(btnmkD, LV_BTNM_STYLE_BG, &style_bg);
    lv_btnm_set_style(btnmkD, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
    lv_obj_align(btnmkP,NULL,LV_ALIGN_IN_TOP_LEFT,0,55);
    lv_obj_align(btnmkI,NULL,LV_ALIGN_IN_TOP_MID,0,55);
    lv_obj_align(btnmkD,NULL,LV_ALIGN_IN_TOP_RIGHT,0,55);

    lv_scr_load(pidScreen);
}
void PIDConstantUpdating(void){
    lv_btnm_set_action(btnmkP, btnmPIDAction);
    lv_btnm_set_action(btnmkI,btnmPIDAction);
    lv_btnm_set_action(btnmkD,btnmPIDAction);
    //lv_scr_load(pidScreen);
}
/* Screen Clear code
lv_init();

// Create a screen object
lv_obj_t *screen = lv_scr_act();

// Clear the screen
lv_obj_clean(screen);
*/		