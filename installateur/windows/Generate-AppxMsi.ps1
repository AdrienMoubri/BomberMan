$WixRoot = "..\wix"
$InstallFileswsx = "..\Template.wxs"
$InstallFilesWixobj = "..\SARP-App.wixobj"

if(!(Test-Path "$WixRoot\candle.exe"))
{    
	Write-Host Downloading Wixtools..
    New-Item $WixRoot -type directory -force | Out-Null
    # Download Wix version 3.10.2 - https://wix.codeplex.com/releases/view/619491
    Invoke-WebRequest -Uri https://wix.codeplex.com/downloads/get/1540241 -Method Get -OutFile $WixRoot\WixTools.zip

    Write-Host Extracting Wixtools..
    Add-Type -AssemblyName System.IO.Compression.FileSystem
    [System.IO.Compression.ZipFile]::ExtractToDirectory("..\wix\WixTools.zip", "..\wix")
}

pushd "$WixRoot"
.\candle.exe $InstallFileswsx -ext WixUtilExtension -o "..\SARP-App.wixobj" 
.\light.exe $InstallFilesWixobj -ext WixUtilExtension -b ".." -o "..\SARP-App.msi" 
popd

#msiexec.exe /i SARP-App.msi /log log.txt
#msiexec.exe /x SARP-App.msi /log log.txt