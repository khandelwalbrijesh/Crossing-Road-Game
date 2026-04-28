# 🚦 Crossing Road Game (C++)

A simple console-based **Crossing Road game** developed in C++ as part of an Object-Oriented Programming course project.

## 🎮 Gameplay

* Control the player using keyboard to avoid enemies and reach the destination.
* Pass 10 lanes to advance to the next level.
* Complete 5 levels to win the game.
* The game ends if the player collides with enemies.

## ⚙️ Features

* 🎯 Multiple levels with increasing difficulty
* 💾 Save & Load game
* ⏸️ Pause menu (Resume / Exit)
* 📖 On-screen instructions
* 🔊 Settings: Sound On/Off
* 🎚️ Difficulty modes: Easy / Hard
* 🎨 Console-based visuals with color support

## 🧠 Technical Overview

### Core Classes

* **Pos (Position):**
  Handles coordinates (x, y) for player and enemies.

* **ConstVar:**
  Stores global settings like:

  * `isMute` (sound on/off)
  * `isHard` (difficulty level)

### Console Utilities

* `gotoXY()` – Move cursor to specific position
* `txtColor()` – Change text color
* `fixConsoleWindow()` – Lock console size
* `NoCursorType()` – Hide cursor

## 🛠️ Technologies

* C++
* Object-Oriented Programming (OOP)
* Console-based UI

## 👤 My Role

* Implemented basic features 
* Tested gameplay and debugged issues
* Prepared project report and documentation

## 📌 Notes

This is a beginner-level academic project, focused on applying OOP concepts and basic game logic in C++.

---

