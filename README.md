<div align="center">

<img src="docs/media/menu.jpg" alt="Veil of Regret title screen" width="100%"/>

# 🕯️ Veil of Regret

### *Every monster is a memory. Every memory wants you dead.*

A hand-built **2D psychological horror** game in **C++ & iGraphics**. Fight your way through a haunted town
where every enemy is one of Aralyn's emotions: Fear, Guilt, Paranoia and, last of all, **Regret**.

<sub>🎓 Built as the **CSE 1200** course project (1st Year, 2nd Semester).</sub>

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![iGraphics](https://img.shields.io/badge/iGraphics-OpenGL%20%2F%20GLUT-5586A4?style=for-the-badge&logo=opengl&logoColor=white)
![Course](https://img.shields.io/badge/Course-CSE%201200-6A0DAD?style=for-the-badge)
![Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Genre](https://img.shields.io/badge/Genre-Psychological%20Horror-8B0000?style=for-the-badge)

[**▶ Watch the Gameplay Trailer**](https://www.youtube.com/watch?v=y2ESBHk0jxs) · [How to Play](#-how-to-play) · [Build & Run](#-build--run)

</div>

---

## 🎬 Trailer

<div align="center">
<a href="https://www.youtube.com/watch?v=y2ESBHk0jxs">
  <img src="https://img.youtube.com/vi/y2ESBHk0jxs/maxresdefault.jpg" alt="Watch the Veil of Regret trailer on YouTube" width="80%"/>
</a>
<br/><sub>Click to watch the full gameplay on YouTube</sub>
</div>

---

## ⚡ By the Numbers

<div align="center">

| 🎞️ **901** | 🎬 **484** | 👹 **16** | 🧩 **3** | ⚔️ **4** | 🧠 **~2,850** |
|:---:|:---:|:---:|:---:|:---:|:---:|
| hand-placed image frames | frames of animated cinematics | enemies across 6 creature types | unique puzzle mechanics | weapons that evolve with the story | lines of hand-written C++ |

</div>

No game engine, no Unity, no Unreal, no AI. Every animation, every collision check and every cutscene runs on raw C++
with iGraphics (OpenGL/GLUT under the hood), with a custom frame-animation system built from scratch.

---

## 📖 The Story

<img src="docs/media/narrative.jpg" alt="Opening narrative" width="100%"/>

> *Aralyn wandered through the mist-choked streets of a city that shouldn't exist, a twisted reflection of her own mind.
> A faded clock on a crumbling tower was frozen at 14:09:03, its ticking long silenced…*

The town is called **Hollowcreek**. It has trapped Aralyn and fills itself with monsters made of her own guilt and fear.
To escape she has to fight them, solve the riddles her mind has left behind, and finally face what she did.
**And the ending isn't what you think.**

---

## 🎥 Fully Animated Cinematics

The story plays out through **484 frames** of frame-by-frame cutscenes, each one synced to its own soundtrack.

<div align="center">

| The Clock Stops | Waking in Hollowcreek | A Memory Resurfaces |
|:---:|:---:|:---:|
| <img src="docs/media/cinematic-clock.gif" width="280"/> | <img src="docs/media/cinematic-intro.gif" width="280"/> | <img src="docs/media/cinematic-memory.gif" width="280"/> |
| *165-frame opening sequence* | *The eye opens* | *Hand-drawn memory flashback* |

</div>

---

## 👹 The Bestiary: Monsters Made of Emotion

Every enemy is a feeling Aralyn never dealt with, and each one has its own **walk, idle, attack and death animations**.

<div align="center">

| | Creature | Represents | Chapter | Count | Damage / hit |
|:---:|:---|:---|:---:|:---:|:---:|
| <img src="docs/media/aralyn.gif" width="110"/> | **Aralyn** | *You* | All | 1 | 5 → 20 |
| <img src="docs/media/fear.gif" width="110"/> | **Fear** | The dread that follows you | I | 1 | 10 |
| <img src="docs/media/reaper.gif" width="110"/> | **Reaper** | Fear of death | I | 2 | 10 |
| <img src="docs/media/guilt.gif" width="110"/> | **Guilt** | What you can't take back (3 variants) | II | 3 | 15 |
| <img src="docs/media/paranoia.gif" width="110"/> | **Paranoia** | The eyes that are always watching | III | 6 | 3 |
| <img src="docs/media/fireworm.gif" width="110"/> | **Fireworm** | Anxiety that burns from within | III | 3 | 7 |
| <img src="docs/media/regret.gif" width="110"/> | **Regret** 💀 | **The final boss** | III | 1 | 15 |

</div>

### How hard each monster hits

<img src="docs/media/chart-enemy-damage.png" alt="Bar chart of enemy damage per hit" width="100%"/>

Paranoia hits the softest, but it comes in **swarms of six**. Chapter III throws 10 enemies at you at once before Regret arrives.

---

## 🗺️ Three Chapters into the Mind

<table>
<tr>
<td width="33%" align="center"><img src="docs/media/level1.jpg"/><br/><b>Chapter I: The Forest of Fear</b><br/><sub>Crack the frozen clock's code, then survive Fear and two Reapers.</sub></td>
<td width="33%" align="center"><img src="docs/media/level2.jpg"/><br/><b>Chapter II: The Swamp of Guilt</b><br/><sub>Pair the emotions that belong together, then face three Guilts at once.</sub></td>
<td width="33%" align="center"><img src="docs/media/level3.jpg"/><br/><b>Chapter III: The Crimson Hollow</b><br/><sub>Answer three riddles, survive the swarm, and confront Regret.</sub></td>
</tr>
</table>

<img src="docs/media/diagram-story-flow.png" alt="Flow of the game from the opening cinematic through all three chapters to the final twist" width="100%"/>

---

## 🧩 Puzzles That Tell the Story

Every puzzle is a clue to what happened to Aralyn, not a random gate.

<table>
<tr>
<td width="50%"><img src="docs/media/puzzle-clock.jpg"/><br/><b>The Frozen Clock</b>: <i>"What time did Hollowcreek's heartbeat stop?"</i> The answer is hidden in the story you just read.</td>
<td width="50%"><img src="docs/media/puzzle-riddle.jpg"/><br/><b>The Riddles</b>: <i>"I am always with you, yet I weigh nothing at all…"</i> Three riddles stand between you and Regret.</td>
</tr>
</table>

### 🐈 A Choice That Matters

<img src="docs/media/choice-cat.jpg" alt="The cat choice" width="100%"/>

After Guilt falls, a stray cat finds Aralyn. **Take it in, or turn it away?** The choice is yours, and Aralyn has to let go of something either way.

---

## ⚔️ An Arsenal That Grows With You

Aralyn's weapon changes as the story goes on.

<div align="center">
<img src="docs/media/aralyn-attack.gif" width="160"/>
</div>

<img src="docs/media/chart-weapons.png" alt="Chart of Aralyn's damage by weapon: 5, 9, 13, 20" width="100%"/>

In Chapter III you can **swap weapons mid-fight**. Use the chainsaw `1` up close, or switch to the gun `2` and fire projectiles from range.

---

## 🛠️ Under the Hood

Built without an engine, on top of the **iGraphics** library (which runs on OpenGL/GLUT behind the scenes):

- **Custom animation engine**: a reusable `Animation` class streams numbered frame sequences with per-clip timing, looping and audio sync. It drives all 484 cinematic frames.
- **Object-oriented combat**: `Enemy` inherits from `Player`, so every monster reuses the same movement, attack-cooldown and health-bar code, with chase-and-attack AI added on top.
- **AABB collision detection** for melee hits and a full **projectile system** for the gun.
- **Infinite scrolling backgrounds** that move with the player.
- **State-driven game flow** that ties menus, narrative screens, puzzles, fights and cutscenes together, with chapter select and restart at any point.
- **Image loading** through `stb_image` and **audio** through the Win32 `PlaySound` API, with 4 soundtracks for menu, intro, cinematics and game over.

<img src="docs/media/diagram-architecture.png" alt="Class diagram: Menu, Levels, Animation, Player, Enemy and PlayerProjectile" width="100%"/>

<img src="docs/media/chart-frames.png" alt="Donut chart: 484 cinematic frames, 329 sprite frames, 88 scene and UI images" width="100%"/>

---

## 🎮 How to Play

| Action | Key |
|:---|:---:|
| Move left / right | `←` `→` |
| Jump | `↑` |
| Attack | `End` |
| Switch to chainsaw (Ch. III) | `1` |
| Switch to gun (Ch. III) | `2` |
| Continue story / confirm puzzle | `Enter` |
| Next narrative page | `Space` |
| Accept / reject the cat | `Page Down` / `Page Up` |
| Skip intro to menu | `Home` |
| Back to chapter select | `Esc` |

**Rules of survival**
- Aralyn starts each fight with **100 HP**.
- Clear all **three chapters** to escape Hollowcreek.
- **Jump** to dodge incoming attacks.
- **Pick enemies off one at a time.** Getting surrounded is how you die.
- A wrong answer to a puzzle can end your run.

---

## 🚀 Build & Run

**Requirements:** Windows · Visual Studio 2013 (or newer with the v120 toolset) · iGraphics (included in this repo)

```bash
git clone https://github.com/isratarna/Veil-of-Regret.git
```

1. Open **`sample veil of regret.sln`** in Visual Studio.
2. **Build → Build Solution**.
3. **Debug → Start Without Debugging**.

> 💡 Run from the project folder so the game can find its `Images/` and `Audio/` directories.

---

<div align="center">

### *Can you face what you've been running from?*

[**▶ Watch the trailer**](https://www.youtube.com/watch?v=y2ESBHk0jxs)

</div>
