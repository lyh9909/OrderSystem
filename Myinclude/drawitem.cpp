#include "drawitem.h"

ItemStyleDesigner::ItemStyleDesigner(QObject *parent) : QStyledItemDelegate(parent)
{

}

ItemStyleDesigner::~ItemStyleDesigner()
{

}

void ItemStyleDesigner::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int radius = 10;
    if(index.isValid())
    {
        painter->save();

        QVariant variant = index.data(Qt::UserRole+1);
        ItemData data = variant.value<ItemData>();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));

        if(option.state.testFlag(QStyle::State_Selected))
        {

            painter->setPen(QPen(Qt::blue));
            painter->setBrush(QColor(51, 153, 255));
            painter->drawPath(path);

        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setPen(QPen(QColor(51, 153, 255)));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }
        else{
            painter->setPen(QPen(Qt::black));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

        //设置位置
        QRect NumicRect = QRect(rect.left() +15, rect.top()+5, rect.width()-30, 30);
        QRect NameRect = QRect(rect.left() +15, rect.top()+35, rect.width()-30, 30);
        QRect circle = QRect(rect.right() -15, rect.top()+10, 5, 5);
        QRect priceRect = QRect(rect.right() -50, rect.bottom()-60, 40, 20);
        QRect labelRect = QRect(priceRect.left()-10, rect.bottom()-61, 10, 20);
        QRect numRect = QRect(rect.right() -60, rect.bottom()-35, 50, 20);

        painter->setBrush(Qt::red);
        painter->setPen(QPen(Qt::red));
        painter->drawEllipse(circle);

        painter->setPen(QPen(Qt::blue));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(NumicRect,Qt::AlignLeft,data.number);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(NameRect,Qt::AlignLeft,data.name);

        painter->setPen(QPen(Qt::red));
        painter->setFont(QFont("Times", 12));
        painter->drawText(labelRect,Qt::AlignLeft, "¥");

        painter->setPen(QPen(Qt::red));
        painter->setFont(QFont("Times", 12));
        painter->drawText(priceRect,Qt::AlignCenter, data.price);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(numRect,Qt::AlignCenter,data.num);

        painter->restore();

    }
}

QSize ItemStyleDesigner::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(250, 100);
}

ItemOrderDesigner::ItemOrderDesigner(QObject *parent) : QStyledItemDelegate(parent)
{

}

ItemOrderDesigner::~ItemOrderDesigner()
{

}

void ItemOrderDesigner::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int radius = 15;
    if(index.isValid())
    {
        painter->save();

        QVariant variant = index.data(Qt::UserRole+1);
        ItemOrderData data = variant.value<ItemOrderData>();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));

        if(option.state.testFlag(QStyle::State_Selected))
        {

            painter->setPen(QPen(Qt::gray));
            painter->setBrush(QColor(51, 153, 255));
            painter->drawPath(path);

        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setPen(QPen(QColor(51, 153, 255)));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }
        else{
            painter->setPen(QPen(Qt::black));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

        //设置位置
        QRect Lab1Rect = QRect(rect.left() +15, rect.top()+5, 50, 30);
        QRect ONumRect = QRect(rect.left() +80, rect.top()+5, 50, 30);
        QRect Lab2Rect = QRect(rect.left() +140, rect.top()+5, 150, 30);
        QRect OrderRect = QRect(rect.left() +290, rect.top()+5, 150, 30);
        QRect ContentRect = QRect(rect.left() +15, rect.top()+40, rect.width() - 100, 50);
        QRect Lab3Rect = QRect(rect.left() +510, rect.top()+5, 140, 30);
        QRect PriceRect = QRect(rect.left() +655, rect.top()+5 , 50, 30);

        painter->setPen(QPen(Qt::blue));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(Lab1Rect,Qt::AlignLeft,"NO : ");

        painter->setPen(QPen(Qt::blue));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(ONumRect,Qt::AlignLeft,data.onumber);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(Lab2Rect,Qt::AlignLeft,"Order Person: ");

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(OrderRect,Qt::AlignLeft,data.order);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14));
        painter->drawText(ContentRect,Qt::AlignLeft, data.content);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(Lab3Rect,Qt::AlignLeft,"Total Price: ¥ ");

        painter->setPen(QPen(Qt::red));
        painter->setFont(QFont("Times", 14, QFont::Bold));
        painter->drawText(PriceRect,Qt::AlignLeft,data.totalprice);

        painter->restore();

    }
}

QSize ItemOrderDesigner::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(840, 110);
}

ItemStatiusDesigner::ItemStatiusDesigner(QObject *parent) : QStyledItemDelegate(parent)
{

}

ItemStatiusDesigner::~ItemStatiusDesigner()
{

}

void ItemStatiusDesigner::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int radius = 12;
    if(index.isValid())
    {
        painter->save();

        QVariant variant = index.data(Qt::UserRole+1);
        ItemStatiusData data = variant.value<ItemStatiusData>();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));

        if(option.state.testFlag(QStyle::State_Selected))
        {

            painter->setPen(QPen(Qt::gray));
            painter->setBrush(QColor(153, 204, 255));
            painter->drawPath(path);

        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setPen(QPen(QColor(51, 153, 255)));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }
        else{
            painter->setPen(QPen(Qt::gray));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

        //设置位置
        QRect Lab1Rect = QRect(rect.left() +15, rect.top()+5, 250, 20);
        QRect NameRect = QRect(rect.left() +15, rect.top()+30, 250, 30);
        QRect Lab2Rect = QRect(rect.left() +270, rect.top()+5, 100, 20);
        QRect CountRect = QRect(rect.left() +270, rect.top()+30, 100, 30);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(Lab1Rect,Qt::AlignHCenter,"Name");

        painter->setPen(QPen(Qt::blue));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(NameRect,Qt::AlignHCenter,data.name);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(Lab2Rect,Qt::AlignHCenter,"Count");

        painter->setPen(QPen(Qt::red));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(CountRect,Qt::AlignHCenter,data.counts);

        painter->restore();

    }
}

QSize ItemStatiusDesigner::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(360, 70);
}


ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

ItemDelegate::~ItemDelegate()
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int radius = 7;
    if(index.isValid())
    {
        painter->save();

        ItemStatus status = (ItemStatus)(index.data(Qt::UserRole).toInt());

        ItemSelect selectStatus = (ItemSelect)(index.data(Qt::UserRole+1).toInt());

        QVariant variant = index.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        QStyleOptionViewItem viewOption(option);//用来在视图中画一个item

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        //QPainterPath画圆角矩形

        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));


        if(option.state.testFlag(QStyle::State_Selected))
        {// 点击任意item
            if(selectStatus == Select)
            {
                painter->setPen(QPen(Qt::gray));
                painter->setBrush(QColor(119, 255, 194, 125)); //设置背景颜色
                painter->drawPath(path);
            }
            else
            {
                painter->setPen(QPen(Qt::gray));
                painter->setBrush(Qt::NoBrush);
                painter->drawPath(path);
            }

        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {// 鼠标停留item
            painter->setPen(QPen(Qt::green));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }
        else{

            if(selectStatus == Select)
            {
                painter->setPen(QPen(Qt::gray));
                painter->setBrush(QColor(225, 225, 225, 225)); //设置背景颜色
                painter->drawPath(path);
            }
            else
            {
                painter->setPen(QPen(Qt::gray));
                painter->setBrush(Qt::NoBrush);
                painter->drawPath(path);
            }
        }

        //绘制数据位置
        QRect nameRect = QRect(rect.left() +10, rect.top(), 100, 30);
        QRect circle = QRect(rect.right() -10, rect.top()+5, 5, 5);
        QRect priceRect = QRect(nameRect.right() +50, rect.top()+10, 50, 20);
        QRect numRect = QRect(nameRect.right() +50, rect.bottom()-30, 100, 30);
//        QRect imageRect = QRect(rect.left() +10,nameRect.bottom()+10,100,50);

//        QRect imageSource = QRect(0,0,30,30);
//        QImage image1(":/new/Pic_/Picture/alipay.png");


        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(nameRect,Qt::AlignLeft,data.name); //绘制菜名

        painter->setPen(QPen(Qt::red));
        painter->setFont(QFont("Times", 10));
        painter->drawText(priceRect,Qt::AlignLeft, QString::number(data.price)); //绘制价格

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(numRect,Qt::AlignLeft,QString::number(data.num)); //绘制数量

//        painter->drawImage(imageRect,image1,imageSource);

        painter->restore();

    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(200, 80);//设置每个item框的大小
}
