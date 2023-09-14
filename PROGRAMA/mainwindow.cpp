#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Neurona::Neurona(){
    id=0;
    voltaje=0;
    posicion_x=0;
    posicion_y=0;
    red=0;
    green=0;
    blue=0;
    sig=nullptr;
}
Neurona::Neurona(int id,float voltaje,int posicion_x,int posicion_y,int red,int green,int blue,Neurona *sig){
    this->id=id;
    this->voltaje=voltaje;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->red=red;
    this->blue=blue;
    this->green=green;
    this->sig=sig;
}

void Admin::agregar_inicio(int id,float voltaje,int posicion_x,int posicion_y,int red,int green,int blue)
{
    Neurona *tmp=new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue,nullptr);
    if(!h){
        h=tmp;
    }else{
        tmp->sig=h;
        h=tmp;
    }
}

void Admin::agregar_final(int id,float voltaje,int posicion_x,int posicion_y,int red,int green,int blue){
    Neurona *tmp=new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue,nullptr);
    if(!h){
        h=tmp;
    }else{
        Neurona *aux = h;
        while (aux->sig != nullptr) {
            aux = aux->sig;
        }
        aux->sig = tmp;
    }
}

void Admin::mostrar(){
    Neurona *aux=h;
    if(h){
        while(aux){
            std::cout<<"Neurona_"<<aux->id<<std::endl;
            std::cout<<"Voltaje: "<<aux->voltaje<<std::endl;
            std::cout<<"posicion en X: "<<aux->posicion_x<<std::endl;
            std::cout<<"Posicion en Y: "<<aux->posicion_y<<std::endl;
            std::cout<<"Rojo: "<<aux->red<<std::endl;
            std::cout<<"Verde: "<<aux->green<<std::endl;
            std::cout<<"Azul: "<<aux->blue<<std::endl;
            aux=aux->sig;
        }
    }
    else{
        std::cout<<"Lista vacia!"<<std::endl;
    }

}

Admin *lis = new Admin();
int id,posicion_x,posicion_y,red,green,blue;
float voltaje;

void MainWindow::limpiarCampos() {
    id = 0;
    voltaje = 0.0;
    posicion_x = 0;
    posicion_y = 0;
    red = 0;
    green = 0;
    blue = 0;

    // También puedes limpiar los valores en los widgets de la interfaz gráfica si es necesario.
    ui->insert_id->clear();
    ui->insert_voltaje->clear();
    ui->pos_x->setValue(0);
    ui->pos_y->setValue(0);
    ui->set_red->setValue(0);
    ui->set_green->setValue(0);
    ui->set_blue->setValue(0);
}
void MainWindow::on_insert_id_textChanged(const QString &arg1)
{
    std::string cadenaStd = arg1.toStdString();

    // Verificar si la cadena es un número válido
    bool esNumeroValido = !cadenaStd.empty() && std::all_of(cadenaStd.begin(), cadenaStd.end(), [](char c) {
        return std::isdigit(static_cast<unsigned char>(c));
    });

    if (esNumeroValido)
    {
        id = std::stoi(cadenaStd);
    }
    else
    {
        // Manejar el caso en que la cadena no sea un número válido
        // Puedes mostrar un mensaje de error o asignar un valor predeterminado, por ejemplo.
        id = 0; // Valor predeterminado
    }
}
void MainWindow::on_insert_voltaje_textChanged(const QString &arg1)
{
    std::string cadenaStd = arg1.toStdString();

    try {
        voltaje = std::stof(cadenaStd);
    } catch (const std::invalid_argument& e) {
        // Manejar el caso en que la cadena no sea un número válido
        // Asignar un valor predeterminado o mostrar un mensaje de error, por ejemplo.
        voltaje = std::numeric_limits<float>::quiet_NaN(); // Valor predeterminado (NaN)
    }
}
void MainWindow::on_pos_x_valueChanged(int arg1)
{
    posicion_x = arg1;
}

void MainWindow::on_pos_y_valueChanged(int arg1)
{
    posicion_y = arg1;
}

void MainWindow::on_set_red_valueChanged(int value)
{
    red = value;
}

void MainWindow::on_set_green_valueChanged(int value)
{
    green = value;
}

void MainWindow::on_set_blue_valueChanged(int value)
{
    blue = value;
}



void MainWindow::on_agregarInicio_clicked()
{
    lis->agregar_inicio(id,voltaje,posicion_x,posicion_y,red,green,blue);
    std::cout<<"Agregado"<<std::endl;
    limpiarCampos();
}


void MainWindow::on_AgregarFinal_clicked()
{
    lis->agregar_final(id,voltaje,posicion_x,posicion_y,red,green,blue);
    std::cout<<"Agregado"<<std::endl;
    limpiarCampos();
}


void MainWindow::on_plainTextEdit_textChanged()
{

    std::cout<<"ola"<<std::endl;
}



void MainWindow::on_mostrar_clicked()
{
    // Crear una cadena para almacenar la información de las neuronas
    QString neuronasInfo;

    Neurona *aux = lis->h;
    if (aux) {
        while (aux) {
            // Construir la cadena con la información de cada neurona
            QString neuronaStr = "Neurona_" + QString::number(aux->id) + ":\n";
            neuronaStr += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            neuronaStr += "Posicion en X: " + QString::number(aux->posicion_x) + "\n";
            neuronaStr += "Posicion en Y: " + QString::number(aux->posicion_y) + "\n";
            neuronaStr += "Rojo: " + QString::number(aux->red) + "\n";
            neuronaStr += "Verde: " + QString::number(aux->green) + "\n";
            neuronaStr += "Azul: " + QString::number(aux->blue) + "\n\n";

            // Agregar la información de la neurona a la cadena principal
            neuronasInfo += neuronaStr;

            aux = aux->sig;
        }
    } else {
        neuronasInfo = "Lista vacia!";
    }

    // Establecer el texto en el QPlainTextEdit
    ui->plainTextEdit->setPlainText(neuronasInfo);
}


