$root_path=Split-Path -Parent $MyInvocation.MyCommand.Definition
$build_path=Join-Path $root_path "build/windows"
$binary_path=Join-Path $root_path "binary.exe"
if(Test-Path -Path $build_path){
    Remove-Item $build_path -Recurse -Force
}
if(Test-Path -Path $binary_path){
    Remove-Item $binary_path -Recurse -Force
}
