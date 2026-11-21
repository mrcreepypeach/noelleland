#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "gameState.h"
#include "settings.h"
#include "noelle.h"
#include "selectionbox.h"

#define gameTime game.gameTime

bool spawnCooldown {false};
bool clearCooldown {false};
bool flashCooldown {false};

// counters

const float defSpawnTimer {0.1f};
const float defClearTimer {1.0f};
const float defFlashTimer {0.5f};

float spawnTimer {0.0f};
float clearTimer {0.0f};
float flashTimer {0.0f};
int clearCountConsec {0};

// noelle vector
std::vector<noelle*> AllNoelles{};

noelle* checkCursorNoelles(){
	Vector2 MousePosition = GetMousePosition();

	for(noelle* N : AllNoelles){
		const float distance = Vector2Distance(N->position, MousePosition);
		if (distance <= 30.0f){
			std::cout << "clicked nole\n";
			return N;
			break;
		}
	}
	return nullptr;
}

int main() {
	// Initialize the window
	InitWindow(1080, 800, "Noelle Land");
	InitAudioDevice();
	SetExitKey(0);

	if (GetSetting<bool>("UncapFPS")){ SetTargetFPS(0); }
	else{ SetTargetFPS(60); }

	SetTargetFPS(0);

	// initialize various things

	Font DRFont = LoadFont("res/fonts/8bitoperator_jve.ttf");

	Image icon = LoadImage("res/soul/dmc.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	Texture2D noelleHead {LoadTexture("res/noelle/spr_headnoelle_0.png")};

	Texture2D cursorTexture = LoadTexture("res/soul/dmc.png");
	if (!game.DEBUG){ HideCursor(); } // hide cursor to use custom one

	std::unordered_map<std::string, Sound> allSounds{
		{"clickSound", LoadSound("res/sounds/click.wav")},
		{"ominousSound", LoadSound("res/sounds/snd_ominous.mp3")},
		{"ominousHell", LoadSound("res/sounds/snd_ominous_hell.wav")},
		{"ominousHellSuper", LoadSound("res/sounds/snd_ominous_hell_super.wav")}
	};

	SetSoundVolume(allSounds["clickSound"], 0.5f);

	// Initialize the settings boxes

	selectionBox allSelectionBoxes[2]{
		selectionBox(
			Vector2{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2},
			"Uncapped Framerate: ",
			GetSetting<bool>("UncapFPS"),
			DRFont
		),
		selectionBox(
			Vector2{static_cast<float>(GetScreenWidth()) / 2, (static_cast<float>(GetScreenHeight()) / 2) + 30},
			"Click Sound: ", 
			GetSetting<bool>("ClickSound"),
			DRFont
		)
	};

	// Main game loop
	while (!WindowShouldClose()) {

		std::string curFPS{"FPS: "};
		curFPS.append(std::to_string(GetFPS()));
		
		std::string curNolCount = std::to_string(AllNoelles.size());

		// Conditional for pause screen

		if (!game.paused){ // if game is currently playing
			gameTime += GetFrameTime();
			// check cooldowns

			if ((gameTime - spawnTimer) >= defSpawnTimer){ spawnCooldown = false; }
			if ((gameTime - clearTimer) >= defClearTimer){ clearCooldown = false; }
			if ((gameTime - flashTimer) >= defFlashTimer){ flashCooldown = false; }

			if (IsKeyPressed(KEY_U)){
				GetSetting<bool>("UncapFPS") = !GetSetting<bool>("UncapFPS");
				if (GetSetting<bool>("UncapFPS")){ SetTargetFPS(0); }
				else{ SetTargetFPS(60); }
			}

			// Input gathering

			if ((IsKeyPressed(KEY_C)) && (gameTime - clearTimer) >= defClearTimer){
				clearTimer = gameTime;
				clearCooldown = true;
				
				// do a little flash
				if ((gameTime - flashTimer) >= defFlashTimer){
					flashTimer = gameTime;
					flashCooldown = true;
				}

				for(noelle* n : AllNoelles){
					delete n;
				}
				AllNoelles.clear();
				if (clearCountConsec >= 5 && clearCountConsec < 10){
					PlaySound(allSounds["ominousHell"]);
				}
				else if (clearCountConsec >= 10){
					PlaySound(allSounds["ominousHellSuper"]);
				}
				else{
					PlaySound(allSounds["ominousSound"]);
				}

				clearCountConsec += 1;
			}

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && spawnCooldown == false){
				// Checking if noelle is close, will play jumpscare animation
				noelle* closestNol = checkCursorNoelles();
				if (closestNol){
					closestNol->triggerAnimation(noelle::animations::jumpscare);
				}
				else{
					if ((gameTime - spawnTimer) >= defSpawnTimer && !closestNol){
						spawnTimer = gameTime;
						AllNoelles.push_back(new noelle(GetMousePosition()));
						clearCountConsec = 0;
					}
				}

				if (GetSetting<bool>("ClickSound")){
					PlaySound(allSounds["clickSound"]);
				}
			}

			// Update noelles

			for (noelle *N : AllNoelles){ N->update(); }
		}
		else{ // if game is paused

		}

		if (IsKeyPressed(KEY_ESCAPE)){
			if (game.paused){ game.paused = false; }
			else{ game.paused = true; }
		}

		// Start drawing
		BeginDrawing();
		if (!game.paused){
			ClearBackground(BLACK);

			// Draw all the noelles
			for (noelle *N : AllNoelles) {N->draw();}

			// Draw current FPS over them

			DrawTextEx(DRFont, curFPS.c_str(), Vector2{0,0}, 30, 1, WHITE);
			DrawTextEx(DRFont, curNolCount.c_str(), Vector2{40,32}, 30, 1, WHITE);
			DrawTexture(noelleHead, 0, 35, WHITE);

			// Draw cursor
			
			DrawTexture(cursorTexture, GetMouseX() - 10, GetMouseY() - 8, WHITE);

			// check if clearing

			if (!((gameTime - flashTimer) >= defFlashTimer) && flashCooldown){
				float fadeProgress = (gameTime - flashTimer) / defFlashTimer;
				
				unsigned char value = static_cast<unsigned char>(255.0f * (1.0f - fadeProgress));
				Color fade;

				if (clearCountConsec > 5 && clearCountConsec < 10){
					fade = {value, 0,0, 255 }; // change color later
				}
				else if (clearCountConsec >= 10){
					fade = {value, 0,0, 255 };
				}
				else{
					fade = {value, value, value, 255 };
				}

				ClearBackground(fade);
			}
		}
		else{ // paused stuff
			ClearBackground(BLACK);
			Vector2 textSize = MeasureTextEx(DRFont, "PAUSED", 50, 1);
			DrawTextEx(DRFont, "PAUSED", Vector2{static_cast<float>(GetScreenWidth() - textSize.x) / 2, 0}, 50, 1, WHITE);

			// Drawing the settings
			for (selectionBox box : allSelectionBoxes){
				box.draw(DRFont);
			}

		}
		EndDrawing();
	}
	// Close the window and clean up resources

	for (auto& [key, s] : allSounds) { UnloadSound(s); }

	UnloadTexture(cursorTexture);

	CloseWindow();
	return 0;
}