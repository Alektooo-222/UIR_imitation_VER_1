param([string] $Config)
$build_folder = 'build'
if (-not(Test-Path -Path $build_folder)) {
    mkdir $build_folder | Out-Null
    Write-Host Build folder is created
}
$dir = Get-Location
Set-Location $build_folder
# cmake -LAH
# cmake --trace .
# cmake --debug-output .
cmake -G Ninja $dir
cmake -DCMAKE_BUILD_TYPE="${Config}" .. 
cmake --build .
Set-Location $dir