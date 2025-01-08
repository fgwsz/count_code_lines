$root_path=Split-Path -Parent $MyInvocation.MyCommand.Definition
$git_path=Join-Path -Path $root_path -ChildPath ".git"
$repo_name=Read-Host "Input Git Repo Name"
cd $root_path
if (Test-Path $git_path) {
    Remove-Item $git_path -Force -Recurse
}
git init
echo "# $repo_name" > README.md
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin "git@github.com:fgwsz/$repo_name.git"
git push -u origin main
