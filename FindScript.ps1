$files = "Injecter64.exe", "Injecter32.exe", "HookDXGI64.dll", "HookDXGI32.dll", "Viewer64.exe"

Get-ChildItem -Path "Program" -Include *.* -File -Recurse | foreach { $_.Delete()}

foreach ($file in $files)
{
	

	$path = Get-ChildItem -Path "" -Filter $file -Recurse -ErrorAction SilentlyContinue -Force
	if ($path)
	{
		Copy-Item $path.FullName -Destination "Program\\"
	}
	else
	{
		Write-Host "Could not find file:" $file
	}
}
