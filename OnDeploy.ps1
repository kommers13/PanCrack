# Этот скрипт запускает процесс развертывания приложения для Windows

$file = ".\RequiredOnDeploy.txt"    # текстовый файл, в котором прописаны файлы, которые останутся
$build_dir = ".\build\Desktop_Qt_6_8_2_MinGW_64_bit-MinSizeRel\"    # директория, в которой изначальный проект и в которой будет развернут наш проект
$qml_dir = $build_dir + "qml"           # директория с qml-файлами
$exe_file = $build_dir + "PanCrackApp.exe"    # исполняемый файл
$required_files = Get-Content -Path $file    # прочитали содержимое файла в виде массива

# развертываем приложение при помощи windeployqt6
windeployqt6 $exe_file --qmldir $qml_dir

# все файлы внутри $build_dir
$files_in_build_dir = Get-ChildItem -Path $build_dir

# удаление ненужных файлов
foreach ($name in $files_in_build_dir) {
    Write-Host $name
    if ( $null -eq ($required_files | Select-String $name -SimpleMatch) ) {    # если объекта в списке нет
        $full_name = $build_dir + $name
        $target = Get-Item $full_name
        if ( $target.PSIsContainer ) {    # если это папка
            Remove-Item $full_name -Recurse
        }
        else {
            Remove-Item $full_name
        }  
    }
 }
