#include "interfacevideo.h"
#include "ui_interfacevideo.h"
#include <QAudioOutput>
#include <QStandardPaths>

InterfaceVideo::InterfaceVideo(bool co, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceVideo)
    , player(new QMediaPlayer(this))  // 🔹 Initialisation de player
    , audioOutput(new QAudioOutput(this))
    , CO(co)
{
    ui->setupUi(this);

    setFixedSize(800,480);
    this->setWindowTitle("Page de Video");

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    QVideoWidget *videoWidget = new QVideoWidget(this);
    ui->widgetVideo->setLayout(new QVBoxLayout());         // widgetVideo doit exister dans .ui
    ui->widgetVideo->layout()->addWidget(videoWidget);
    player->setVideoOutput(videoWidget);
    videoWidget->show();

    connect(player,&QMediaPlayer::durationChanged,this,[=](qint64 duration){
        ui->horizontalSlider->setRange(0, static_cast<int>(duration));
    });

    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->horizontalSlider->setValue(static_cast<int>(position));
    });


    setFixedSize(800,480);

    this->setWindowTitle("Interface Vidéo");

    QPixmap imagePlay(":/images/Play"); // Charge l'image
    if (imagePlay.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePlay); // Crée une icône
        ui->pushButton_Play->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Play->setIconSize(ui->pushButton_Play->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imagePause(":/images/Pause"); // Charge l'image
    if (imagePause.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePause); // Crée une icône
        ui->pushButton_Pause->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Pause->setIconSize(ui->pushButton_Pause->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageAvant10(":/images/Avant10"); // Charge l'image
    if (imageAvant10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageAvant10); // Crée une icône
        ui->pushButton_Avant10->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Avant10->setIconSize(ui->pushButton_Avant10->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageApres10(":/images/Apres10"); // Charge l'image
    if (imageApres10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageApres10); // Crée une icône
        ui->pushButton_Apres10->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Apres10->setIconSize(ui->pushButton_Apres10->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    ui->pushButton_Pause->setVisible(true);
    ui->pushButton_Play->setVisible(false);
}

InterfaceVideo::~InterfaceVideo()
{
    delete ui;
}

void InterfaceVideo::on_pushButton_SelectVideo_clicked()
{
    QString videoPath = "\\\\192.168.64.2\\Activites";  // Chemin réseau de la Raspberry Pi

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner une vidéo",
        videoPath,  // Ouvre directement le dossier réseau
        "Vidéos (*.mp4 *.avi *.mkv *.mov *.wmv)"  // Filtre les fichiers vidéo
        );

    if (!fileName.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(fileName));  // Charger et lire la vidéo
        player->play();
        qDebug() << "Fichier sélectionné : " << fileName;
    }
}

void InterfaceVideo::on_pushButton_Avant10_clicked()
{
    animateButtonClick(ui->pushButton_Avant10);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition - 10000;
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}
void InterfaceVideo::on_pushButton_Apres10_clicked()
{
    animateButtonClick(ui->pushButton_Apres10);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition + 10000;
    player->setPosition(newPosition);
}

void InterfaceVideo::on_pushButton_Play_clicked()
{
    player->play();
    ui->pushButton_Pause->setVisible(true);
    ui->pushButton_Play->setVisible(false);
}

void InterfaceVideo::on_pushButton_Pause_clicked()
{
    player->pause();
    ui->pushButton_Pause->setVisible(false);
    ui->pushButton_Play->setVisible(true);
}
void InterfaceVideo::on_horizontalSlider_sonVideo_actionTriggered(int action)
{
    int volume = ui->horizontalSlider_sonVideo->value();  // Récupère la valeur du slider
    audioOutput->setVolume(volume / 100.0);
}

void InterfaceVideo::closeEvent(QCloseEvent *event)
{
    if (player) {
        player->stop();
        delete player;
        player = nullptr;
    }
    event->accept();
}
void InterfaceVideo::on_horizontalSlider_sliderReleased()
{
    int position = ui->horizontalSlider->value();  // récupère la position du curseur
    player->setPosition(position);
}
void InterfaceVideo::animateButtonClick(QPushButton* btn) {
    // 1) on prend la géométrie d'origine
    const QRect orig = btn->geometry();
    const QRect small = orig.adjusted(5, 5, -5, -5);

    // 2) animation pour rétrécir
    auto *shrink = new QPropertyAnimation(btn, "geometry");
    shrink->setDuration(50);
    shrink->setStartValue(orig);
    shrink->setEndValue(small);

    // 3) animation pour réagrandir
    auto *expand = new QPropertyAnimation(btn, "geometry");
    expand->setDuration(50);
    expand->setStartValue(small);
    expand->setEndValue(orig);

    // 4) on les enchaîne
    auto *seq = new QSequentialAnimationGroup(btn);
    seq->addAnimation(shrink);
    seq->addAnimation(expand);

    // 5) on lance et on supprime l’objet à la fin
    seq->start(QAbstractAnimation::DeleteWhenStopped);
}
