#include "imageprocessor.h"
#include <QApplication>
#include <QDebug>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Easy Word"));
    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);
    //在工具栏上嵌入控件
    //设置字体
    fontLabel = new QLabel(tr("字体:"));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);
    fontLabel2 = new QLabel(tr("字号:"));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach(int size,db.standardSizes())
    sizeComboBox->addItem(QString::number(size));
    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon("bold.png"));
    boldBtn->setCheckable(true);
    italicBtn= new QToolButton;
    italicBtn->setCheckable(true);
    underlineBtn = new QToolButton;
    underlineBtn->setIcon(QIcon("underline.png"));
    underlineBtn->setCheckable(true);
    colorBtn = new QToolButton;
    colorBtn->setIcon(QIcon("color.png"));
    colorBtn->setCheckable(true);


    createAction();
    createMenu();
    createToolBars();
    if (img.load("image.png")){
//        qDebug()<<tr("tuxiang")<<endl;
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
        //在imageLabel中放置图像
    }
    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(ShowFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked()),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(ShowItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked()),this,SLOT(ShowUnderlineBtn()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(ShowColorBtn()));
    connect(showWidget->text,SIGNAL(currnetCharFormatChanged(QtextCharFormat&)),this,SLOT(ShowCurrentFormatChanged(QTextCharFormat&)));
}

ImageProcessor::~ImageProcessor()
{
}

void ImageProcessor::createAction() {
openFileAction = new QAction(QIcon("open.png"),tr("打开"),this);
openFileAction->setShortcut(tr("Ctrl+o"));
openFileAction->setStatusTip(tr("打开一个文件"));
connect(openFileAction,SIGNAL(triggered()),this,SLOT(ShowOpenFile()));
NewFileAction = new QAction(QIcon("new.png"),tr("新建"),this);
NewFileAction->setShortcut(tr("Ctrl+N"));
NewFileAction->setStatusTip(tr("新建一个文件"));
connect(NewFileAction,SIGNAL(triggered()),this,SLOT(ShowNewFile()));

exitAction = new QAction(tr("退出"),this);
exitAction->setShortcut(tr("Ctrl+Q"));
exitAction->setStatusTip(tr("退出程序"));
connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
copyAction = new QAction(QIcon("copy.png"),tr("复制"),this);
copyAction->setShortcut(tr("Ctrl+C"));
copyAction->setStatusTip(tr("复制文件"));
connect(copyAction,SIGNAL(triggered()),showWidget->text,SLOT(copy()));

cutAction = new QAction(QIcon("cut.png"),tr("剪切"),this);
cutAction->setStatusTip(tr("剪切文件"));
cutAction->setShortcut(tr("Ctrl+X"));
connect(cutAction,SIGNAL(triggered()),showWidget->text,SLOT(cut()));

pasteAction = new QAction(QIcon("paste.png"),tr("粘贴"),this);
pasteAction->setShortcut(tr("Ctrl+p"));
pasteAction->setStatusTip(tr("粘贴文件"));
connect(pasteAction,SIGNAL(triggered()),showWidget->text,SLOT(paste()));

aboutAction = new QAction(tr("关于"),this);
connect(aboutAction,SIGNAL(triggered()),this,SLOT(QApplication::aboutQt()));

PrintTextAction = new QAction(QIcon("printText.png"),tr("打印文本"),this);
PrintTextAction->setStatusTip(tr("打印一个文本"));
PrintImageAction = new QAction(QIcon("printImage.png"),tr("打印图像"),this);
PrintImageAction->setStatusTip(tr("打印一幅图像"));
connect(PrintTextAction,SIGNAL(triggered()),this,SLOT(ShowPrintText()));
connect(PrintImageAction,SIGNAL(triggered()),this,SLOT(ShowPrintImage()));
zoomInAction = new QAction(QIcon("zoomin.png"),tr("放大"),this);
zoomInAction->setStatusTip(tr("放大一张图片"));
connect(zoomInAction,SIGNAL(triggered()),this,SLOT(ShowZoomIn()));
zoomOutAction = new QAction(QIcon("zoomout.png"),tr("缩小"),this);
zoomOutAction->setStatusTip(tr("缩小一张图片"));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(ShowZoomOut()));

rotate90Action = new QAction(QIcon("rotate90.png"),tr("旋转90度"), this);
rotate90Action->setStatusTip(tr("将一幅图像旋转90度"));
rotate180Action = new QAction(QIcon("rotate180.png"),tr("旋转180度"), this);
rotate180Action->setStatusTip(tr("将一幅图像旋转180度"));
rotate270Action = new QAction(QIcon("rotate270.png"),tr("旋转270度"), this);
rotate270Action->setStatusTip(tr("将一幅图像旋转270度"));
connect(rotate90Action,SIGNAL(triggered()),this,SLOT(ShowRotate90()));
connect(rotate180Action,SIGNAL(triggered()),this,SLOT(ShowRotate180()));
connect(rotate270Action,SIGNAL(triggered()),this,SLOT(ShowRotate270()));

mirrorVerticalAction = new QAction(QIcon("mirrorVertical.png"),tr("纵向镜像"),this);
mirrorVerticalAction->setStatusTip(tr("对一张图做纵向镜像"));

connect(mirrorVerticalAction,SIGNAL(triggered()),this,SLOT(ShowMirrorVertical()));
mirrorHorizontalAction = new QAction(QIcon("mirrorHorizontal.png"),tr("横向镜像"),this);
mirrorHorizontalAction->setStatusTip(tr("对一张图做横向镜像"));
    connect(mirrorHorizontalAction,SIGNAL(triggered()),this,SLOT(ShowMirrorHorizontal()));


undoAction = new QAction(QIcon("undo.png"),"撤销",this);
connect(undoAction,SIGNAL(triggered()),showWidget->text,SLOT(undo()));
redoAction = new QAction(QIcon("redo.png"),"重做",this);
connect(redoAction,SIGNAL(triggered()),showWidget->text,SLOT(redo()));
}

void ImageProcessor::createMenu() {
fileMenu = menuBar()->addMenu(tr("文件"));
fileMenu->addAction(openFileAction);
fileMenu->addAction(NewFileAction);
fileMenu->addAction(PrintTextAction);
fileMenu->addAction(PrintImageAction);
fileMenu->addSeparator();
fileMenu->addAction(exitAction);
zoomMenu = menuBar()->addMenu(tr("编辑"));
zoomMenu->addAction(copyAction);
zoomMenu->addAction(cutAction);
zoomMenu->addAction(pasteAction);
zoomMenu->addAction(aboutAction);
zoomMenu->addSeparator();
zoomMenu->addAction(zoomInAction);
zoomMenu->addAction(zoomOutAction);

rotateMenu = menuBar()->addMenu(tr("旋转"));
rotateMenu->addAction(rotate90Action);
rotateMenu->addAction(rotate180Action);
rotateMenu->addAction(rotate270Action);

mirrorMenu = menuBar()->addMenu(tr("镜像"));
mirrorMenu->addAction(mirrorVerticalAction);
mirrorMenu->addAction(mirrorHorizontalAction);

}

void ImageProcessor::createToolBars() {
fileTool = addToolBar("File");
fileTool->addAction(openFileAction);
fileTool->addAction(NewFileAction);
fileTool->addAction(PrintTextAction);
fileTool->addAction(PrintImageAction);

zoomTool = addToolBar("Edit");
zoomTool->addAction(copyAction);
zoomTool->addAction(cutAction);
zoomTool->addAction(pasteAction);
zoomTool->addSeparator();
zoomTool->addAction(zoomInAction);
zoomTool->addAction(zoomOutAction);
rotateTool =addToolBar("rotate");
rotateTool->addAction(rotate90Action);
rotateTool->addAction(rotate180Action);
rotateTool->addAction(rotate270Action);
doToolBar = addToolBar("doEdit");
doToolBar->addAction(undoAction);
doToolBar->addAction(redoAction);
fontToolBar = addToolBar("Font");
fontToolBar->addWidget(fontLabel);
fontToolBar->addWidget(fontComboBox);
fontToolBar->addWidget(fontLabel2);
fontToolBar->addWidget(sizeComboBox);
fontToolBar->addSeparator();
fontToolBar->addWidget(boldBtn);
fontToolBar->addWidget(italicBtn);
fontToolBar->addWidget(underlineBtn);
fontToolBar->addSeparator();
fontToolBar->addWidget(colorBtn);


}



void ImageProcessor::mergeFormat(QTextCharFormat format) {
QTextCursor cursor = showWidget->text->textCursor();//获得编辑框中的光标
if (!cursor.hasSelection())
    cursor.select(QTextCursor::WordUnderCursor);//若光标没有高亮选区 则将光标所在处的词作为选区 由前后空格或 , .等标点符号作为分词
    cursor.mergeCharFormat(format);//调用QTextCursor的mergeCharFormat() 的merge CurrentCharFormat 函数将参数format所表示的格式应用到光标所在处的字符上
    showWidget->text->mergeCurrentCharFormat(format);//调用QTextEdit的merge

}

void ImageProcessor::ShowNewFile() {
ImageProcessor *newImgProcessor = new ImageProcessor;
newImgProcessor->show();
}
#include <QFileDialog>
void ImageProcessor::ShowOpenFile() {
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
        if(showWidget->text->document()->isEmpty()){
            loadFile(fileName);
        }
        else{
            ImageProcessor *newImgProcessor = new ImageProcessor;
            newImgProcessor->show();
            newImgProcessor->loadFile(fileName);
        }
    }
}
void ImageProcessor::loadFile(QString filename) {
    printf("file name:%s\n",filename.data());
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream textStream(&file);
        while (!textStream.atEnd()){
            showWidget->text->append(textStream.readLine());
            printf("readline\n");
        }
        printf("end\n");
    }
}
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

void ImageProcessor::ShowPrintText() {
QPrinter printer;
QPrintDialog printDialog(&printer,this);
if (printDialog.exec()){
    QTextDocument *doc = showWidget->text->document();
    doc->print(&printer);
}

}
#include <QPainter>
void ImageProcessor::ShowPrintImage() {
QPrinter printer;
QPrintDialog printDialog(&printer,this);
if (printDialog.exec()){
    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = img.size();
    size.scale(rect.size(),Qt::KeepAspectRatio);
    painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
    painter.setWindow(img.rect());
    painter.drawImage(0,0,img);
}
}

void ImageProcessor::ShowZoomIn() {
if (img.isNull()){
    return;
}
QMatrix matrix;
matrix.scale(2,2);
img = img.transformed(matrix);
showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}
void ImageProcessor::ShowZoomOut() {
    if (img.isNull()){
        return;
    }
    QMatrix matrix;
    matrix.scale(0.5,0.5);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowRotate90() {
if (img.isNull()){
    return;
}
QMatrix matrix;
matrix.rotate(90);
img = img.transformed(matrix);
showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImageProcessor::ShowRotate180() {
    if (img.isNull()){
        return;
    }
    QMatrix matrix;
    matrix.rotate(180);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImageProcessor::ShowRotate270() {
    if (img.isNull()){
        return;
    }
    QMatrix matrix;
    matrix.rotate(270);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImageProcessor::ShowMirrorVertical() {
if (img.isNull()){
    return;
}
img = img.mirrored(false,true);
showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImageProcessor::ShowMirrorHorizontal() {
    if (img.isNull()){
        return;
    }
    img = img.mirrored(true, false);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImageProcessor::ShowFontComboBox(QString comboStr) {
QTextCharFormat fmt;
fmt.setFontFamily(comboStr);
mergeFormat(fmt);
}

void ImageProcessor::ShowSizeSpinBox(QString spinValue) {//设置文字字号大小
QTextCharFormat fmt;
fmt.setFontPointSize(spinValue.toFloat());
showWidget->text->mergeCurrentCharFormat(fmt);

}

void ImageProcessor::ShowBoldBtn() {
QTextCharFormat fmt;
fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
showWidget->text->mergeCurrentCharFormat(fmt);
qDebug()<<"123456"<<endl;
/*
 *文字的粗细值由QFont::Weight 表示 他是一个整数 取值范围为0-99 有五个预设的额值 分别为
 * QFont::Light(25)
 * QFont::Normal(50)
 * QFont::DemiBold(63)
 * QFont::Bold(75)
 * QFont::Black(87)
 * 一般都是在Normal和Bold之间转换
 * */
}

void ImageProcessor::ShowItalicBtn() {
    /*
     * 设置斜体字
     * */
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);

}

void ImageProcessor::ShowUnderlineBtn() {
QTextCharFormat fmt;
fmt.setFontUnderline(underlineBtn->isChecked());
showWidget->text->mergeCurrentCharFormat(fmt);
}
#include <QColorDialog>
#include <QColor>
void ImageProcessor::ShowColorBtn() {
QColor color = QColorDialog::getColor(Qt::red,this);
if (color.isValid()){
    QTextCharFormat fmt;
    fmt.setForeground(color);
    showWidget->text->mergeCurrentCharFormat(fmt);
}
}

void ImageProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt) {
fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
boldBtn->setChecked(fmt.font().bold());
italicBtn->setChecked(fmt.fontItalic());
underlineBtn->setChecked(fmt.fontUnderline());
}
