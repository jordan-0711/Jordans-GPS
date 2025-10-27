# Jordan’s GPS Mod — DayZ Standalone

A lightweight gameplay expansion that introduces a **craftable GPS navigation device** into DayZ.

Survivors must salvage and assemble real electronic components. No freebies. If you want advanced navigation, earn it.

---

## Features

- **Electronics Salvage:** Dismantle radios, panels, and lighting gear for usable parts.
- **Electrical Hazards:** Powered devices can shock the player; severity depends on battery type and wetness.
- **Wet Work Risks:** Cutting in wet conditions may cause slips; gloves can mitigate injuries.
- **State Inheritance:** Salvaged parts inherit condition and wetness realistically.
- **Clean Recipes:** Each step uses validated DayZ recipe patterns.
- **Localization-Ready:** Item names, descriptions, and messages use `stringtable.xml` keys.

---

## Progression (v1)

### 1) Cut Wires
- Sources: Cable reel / spotlight  
- Tools: Knives, axes, saws  
- Risk: Wet surfaces increase slip chance (gloves reduce harm)  
**Result:** `Wire cuttings`

### 2) Dismantle Radio for PCB / Wires
- Sources: Base Radio, Personal Radio, PAS panel  
- Tool: Screwdriver  
- Risk: Shock if powered (9V small; car battery stronger; wet = worse)  
**Result:** `Salvaged PCB` **or** `Wire cuttings` (50/50)

### 3) Craft Wired PCB
- Ingredients: `Wire cuttings` + `Salvaged PCB`  
- Requirement: **Both must be dry** (recipe blocked if damp/wet)  
**Result:** `Wired GPS PCB`

### 4) Assemble GPS Receiver
- Final Stage: Install wired PCB into casing  
**Result:** Vanilla **GPS Receiver** (uses DayZ in-game map system)

---

## Design Goals

- Extend mid-game electronic survival tasks  
- Balance risk/reward for modern tech recovery  
- Respect vanilla DayZ balance (no free GPS spawning)  
- Reward teamwork, scavenging, and preparedness

---

## Roadmap (Short)

- GPS casing/model polish  
- Additional salvage sources in industrial zones  
- Optional hardcore toggle: map requires installed battery

---

## Install

Pack as a standard DayZ mod PBO. Ensure:
- `CfgPatches.requiredAddons[]` covers the base classes you extend (e.g., `DZ_Data`, `DZ_Radio`, `DZ_Gear_Camping`, `DZ_Gear_Navigation`, `DZ_Scripts` as needed).
- `CfgMods/defs/worldScriptModule/files[]` points to your `Scripts/4_World` folder.
- `stringtable.xml` is at PBO root (same level as `config.cpp`).

---

## Credits & License

Created and maintained by **Jordan Woods**.  
Issues and PRs welcome.

> If you’re expanding electronics/crafting gameplay for DayZ, feel free to open a discussion.
