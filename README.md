# Apex Strike Framework

This is our graduation project. It's a proof-of-concept (PoC) framework built to understand how modern malware evades antivirus and steals data. 

We kept the scope focused on the two most critical parts of an attack: getting past Windows Defender, and exfiltrating data out of a restricted network. We did not build a full Remote Access Trojan (RAT), as the goal was to study the mechanics, not build a weapon.

## What's Inside

**1. Evasion Module (`1_Evasion_Module`)**
*   **File:** `DefenderBypass.exe`
*   **How it works:** It uses XOR obfuscation to hide text strings from static analysis and uses static linking to avoid missing DLL errors. 
*   **Proof:** When you run it, Windows Defender doesn't flag it, and it drops a `Defender_Bypassed.txt` file on the Desktop.

**2. Exfiltration Module (`2_Exfiltration_Module`)**
*   **File:** `SimpleExfil.exe`
*   **How it works:** VirtualBox network isolation blocks direct connections to a C2 server. To get around this, this module uses "Living off the Land" (LOTL). It uses the native Windows `curl.exe` tool to package stolen files and screenshots, and uploads them to a Discord Webhook.
*   **Proof:** Run it, and a `.zip` file with the stolen data appears in the Discord channel.

**Source Code (`3_Source_Code`)**
The raw C code for both modules is here so you can see exactly how they work.

## Why we Built It This Way
The hardest part of this project wasn't the code, it was dealing with the network restrictions in the virtual machine. Instead of giving up, we pivoted to using legitimate Windows tools (`curl.exe`) and external services (Discord) to bypass the block, which is exactly how real APTs operate in restricted environments.
<br>
<br>
<br>
## Future Development
<br>
Apex Strike Framework is an evolving project, and we plan to introduce new features and improvements in future versions. Our long-term vision is to expand its compatibility with Linux, Android, and other platforms.
<br>
<br>
## Roles
<br>
To ensure a comprehensive development process, we divided the project into four key areas: Core Development, Evasion & Security, Network Infrastructure, and QA & Documentation. This allowed us to specialize and focus deeply on each component while collaborating on the final integration.
<br>
1.Kalkidan Ayele: Core Developer (Implant Architect) 
<br>
           Focus: Writing the C code for the Windows Implant (implant.c).
           <br>
2.Yanet Bedilu: Evasion & Security Researcher
<br>
         Focus: Defeating Windows Defender, Anti-Debugging, and VM Detection.
         <br>
3.Kalkidan Solomon:  Network & C2 Engineer
<br>
             Focus: WinHTTP API, XOR Encryption, and Server Infrastructure.
             <br>
4.Bitanya Tsegaye:  QA & Documentation Lead
<br>
            Focus: Testing, debugging, and creating the final presentation.
            <br>

*Note: This was built strictly for educational purposes to understand defensive evasion.*
