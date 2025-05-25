# ���� ������ ��������� ������� ������������� ���������� ��� Windows

$file = ".\RequiredOnDeploy.txt"    # ��������� ����, � ������� ��������� �����, ������� ���������
$build_dir = ".\build\Desktop_Qt_6_8_2_MinGW_64_bit-MinSizeRel\"    # ����������, � ������� ����������� ������ � � ������� ����� ��������� ��� ������
$qml_dir = $build_dir + "qml"           # ���������� � qml-�������
$exe_file = $build_dir + "PanCrackApp.exe"    # ����������� ����
$required_files = Get-Content -Path $file    # ��������� ���������� ����� � ���� �������

# ������������ ���������� ��� ������ windeployqt6
windeployqt6 $exe_file --qmldir $qml_dir

# ��� ����� ������ $build_dir
$files_in_build_dir = Get-ChildItem -Path $build_dir

# �������� �������� ������
foreach ($name in $files_in_build_dir) {
    Write-Host $name
    if ( $null -eq ($required_files | Select-String $name -SimpleMatch) ) {    # ���� ������� � ������ ���
        $full_name = $build_dir + $name
        $target = Get-Item $full_name
        if ( $target.PSIsContainer ) {    # ���� ��� �����
            Remove-Item $full_name -Recurse
        }
        else {
            Remove-Item $full_name
        }  
    }
 }
