#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include "showwidget.h"


class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();
    void createAction();
    void createMenu();
    void createToolBars();
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat format);

private:
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;

    QImage img;
    QString fileName;
    ShowWidget *showWidget;
    QAction *openFileAction;
    QAction *NewFileAction;
    QAction *PrintTextAction;
    QAction *PrintImageAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *rotate90Action;
    QAction *rotate180Action;
    QAction *rotate270Action;

    QAction *mirrorVerticalAction;
    QAction *mirrorHorizontalAction;
    QAction *undoAction;
    QAction *redoAction;
    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;
    QToolBar *doToolBar;
    QLabel *fontLabel;//字体设置选项
    QFontComboBox *fontComboBox;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;
    QToolBar *fontToolBar;//字体工具栏

    QLabel *listLabel;
    QComboBox *listComboBox;
    QActionGroup *actGrp;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QToolBar *listToolBar;


protected slots:
    void ShowNewFile();
void ShowOpenFile();
void ShowPrintText();
void ShowPrintImage();
void ShowZoomIn();
void ShowZoomOut();
void ShowRotate90();
void ShowRotate180();
void ShowRotate270();
void ShowMirrorVertical();
void ShowMirrorHorizontal();
void ShowFontComboBox(QString comboStr);
void ShowSizeSpinBox(QString spinValue);
void ShowBoldBtn();
void ShowItalicBtn();
void ShowUnderlineBtn();
void ShowColorBtn();
void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

void ShowList(int);
void ShowAlignment(QAction *act);
void ShowCursorPositionChanged();
};
#endif // IMAGEPROCESSOR_H
