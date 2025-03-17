#pragma once
#include <chrono>

#include "iGraphics.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")  // Link Windows multimedia library

class Animation {
private:
	std::vector<int> frames;  // Stores image IDs
	bool repeatable;          // Should the animation repeat?
	int intervalMS;           // Frame change interval (in milliseconds)
	bool isFinished;          // Flag to check if animation ended
	std::string soundPath;    // Path to the sound file
	bool soundPlaying;        // Is sound currently playing?
	bool started;             // Flag to indicate animation has started

	std::chrono::steady_clock::time_point lastFrameTime; // Track time between frame updates

public:
	int frameIndex;           // Current animation frame
	int totalFrames;          // Total number of frames
	bool loopSound;

	// Constructor: Load images automatically but don't start immediately
	Animation(const std::string& folder, const std::string& filePrefix, int totalFrames, bool isRepeatable, int intervalMS, const std::string& soundFile = "", bool loopSound = false)
		: frameIndex(0), totalFrames(totalFrames), repeatable(isRepeatable), intervalMS(intervalMS), isFinished(false),
		soundPath(soundFile), soundPlaying(false), loopSound(loopSound), started(false) {

		preloadImages(folder, filePrefix);
	}

	bool is_finished() const {
		return isFinished;
	}

	bool isLastFrameRendered() const {
		return is_finished() && frameIndex == totalFrames - 1;
	}

	// **Lazy loading approach:** Preload images once before the game starts
	void preloadImages(const std::string& folder, const std::string& filePrefix) {
		std::string framePath;
		for (int i = 0; i < totalFrames; i++) {
			framePath = folder + "/" + filePrefix + " (" + std::to_string(i + 1) + ").png";
			int imageID = iLoadImage(const_cast<char*>(framePath.c_str()));

			if (imageID == -1) {
				std::cerr << "Failed to load image: " << framePath << std::endl;
			}
			frames.emplace_back(imageID);
		}
	}

	// Play sound if available
	void playSound() {
		if (!soundPath.empty() && !soundPlaying) {
			int flags = SND_FILENAME | SND_ASYNC;
			if (loopSound) {
				flags |= SND_LOOP;  // Add loop flag if sound should play indefinitely
			}
			PlaySound(soundPath.c_str(), NULL, flags);
			soundPlaying = true;
		}
	}

	// Stop sound if looping is not enabled
	void stopSound() {
		if (!loopSound) {
			PlaySound(NULL, NULL, 0);  // Stop only if not looping indefinitely
			soundPlaying = false;
		}
	}

	// Start the animation (should be called when it's actually needed)
	void start() {
		if (!started) {
			started = true;
			lastFrameTime = std::chrono::steady_clock::now(); // Start frame timer
			playSound();
		}
	}

	// Update animation frame based on time
	void updateFrame() {
		if (!started || isFinished) return;  // Do nothing if animation hasn't started or is finished

		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

		if (elapsed >= intervalMS) {
			frameIndex++;
			lastFrameTime = now; // Reset timer for next frame update

			if (frameIndex >= totalFrames) {
				if (repeatable) {
					frameIndex = 0;  // Loop animation
				}
				else {
					frameIndex = totalFrames - 1;  // Stop at last frame
					isFinished = true;
					stopSound();
				}
			}
		}
	}

	// Render the animation
	void render(int x, int y, int width, int height) {
		if (!frames.empty() && started) {
			iShowImage(x, y, width, height, frames[frameIndex]);
		}
	}

	// Reset animation state but don't start immediately
	void reset() {
		frameIndex = 0;
		isFinished = false;
		started = false;  // Prevent immediate playback
	}

	// Check if the animation has finished (for non-repeatable animations)
	bool hasFinished() const {
		return isFinished;
	}

	// Get the interval time for the iGraphics timer
	int getInterval() const {
		return intervalMS;
	}
};
