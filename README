Property module provide widget for handling properties for QObject(s).

HOW TO USE:
  -  Step 1
           Copy "property" folder to your application

  -  Step 2
           Include property.pri in your PRO file

           Example:
           include("src/property/property.pri")

  -  Step 3
           Create ObjectController in necessary place

           Example:
             ObjectController *controller=new ObjectController(this);
             ui->myLayout->addWidget(controller);

  -  Step 4
           Set objects for handling

           Example:
             controller->setObject(ui->testButton);

             or

             QObjectList objects;
             objects.append(ui->previewFrame);
             ...
             objects.append(ui->anotherThing);
             controller->setObjects(objects);

TIPS:
  - You can filter some group of properties (class properties) or specific properties by overriding "filterClass" and "filterProperty" methods.

  - To handle newly created property in ObjectController override "propertyAdded" method.

  - You can create your own editor for ObjectController. To do that, you need to create widget inherited from CustomEditor and create delegate inherited from CustomDelegate. After that override "create...Delegate" method in ObjectController.

  - To provide selection for property with QString type you can create public slot (bool valuesForProperty(QString aPropertyName, QStringList &aValues);) or use "values" attribute

           Example:
             bool TestObject::valuesForProperty(QString aPropertyName, QStringList &aValues)
             {
                 if (aPropertyName=="StringCombo")
                 {
                     aValues.append("Option 1");
                     aValues.append("Option 2");
                     aValues.append("Option 3");
                     aValues.append("Option 4");
                     aValues.append("Option 5");
                     aValues.append("Option 6");

                     return true;
                 }

                 return false;
             }

             or

             Q_CLASSINFO("StringCombo attributes", "values : Value1|Value2|Value3;")

  - Also it is possible customize your properties by using attributes. To write attributes for property you need to keep format below:

           Q_CLASSINFO("PROPERTY_NAME attributes", "ATTRIBUTE_NAME : VALUE ;")

           PROPERTY_NAME - it is a name of property.
           ATTRIBUTE_NAME - it is a name of attribute. Please check for attributes in examples below.
           VALUE - specific for each attribute.
           : - character to separate ATTRIBUTE_NAME and VALUE.
           ; - character to separate attributes

           Please note that ATTRIBUTE_NAME and VALUE will be trimmed. So, if you want to use whitespaces in VALUE you need to use \" character

           There are general attributes for any property:
               toolTip - it is a toolTip.
               delay - delay between changing value and applying it to the object. Used for quickly modified properties (int, QString, QDateTime, etc.).
               default - default value that looks like a text in object controller. If value not the same as default value it will be highlighted.
               paletteRoleColor - to change color for some palette role (example: "baseColor : #FF0000;")

           Examples:
Q_CLASSINFO("Enumeration attributes", "toolTip            : \"It is a Enumeration\" ;"
                                      "delay              : 100 ;"
                                      "default            : ENUM_TWO ;"
                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"
           )

Q_CLASSINFO("Flags attributes",       "toolTip            : \"It is a Flags\" ;"
                                      "delay              : 100 ;"
                                      "default            : [FLAG_1, FLAG_3] ;"
           )

Q_CLASSINFO("StringCombo attributes", "toolTip            : \"It is a StringCombo\" ;"
                                      "delay              : 100 ;"
                                      "default            : Option 1 ;"
                                    //"maxVisibleItems    : 5 ;"
                                      "editable           : true ;"
                                      "values             : Value1|Value2|Value3 ;"
           )

Q_CLASSINFO("Bool attributes",        "toolTip            : \"It is a Bool\" ;"
                                      "delay              : 100 ;"
                                      "default            : true ;"
           )

Q_CLASSINFO("Int8 attributes",        "toolTip            : \"It is a Int8\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 1 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("UInt8 attributes",       "toolTip            : \"It is a UInt8\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 2 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Int16 attributes",       "toolTip            : \"It is a Int16\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 3 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("UInt16 attributes",      "toolTip            : \"It is a UInt16\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 4 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Int32 attributes",       "toolTip            : \"It is a Int32\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 5 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("UInt32 attributes",      "toolTip            : \"It is a UInt32\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 6 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Int64 attributes",       "toolTip            : \"It is a Int64\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 7 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("UInt64 attributes",      "toolTip            : \"It is a UInt64\" ;"
                                      "delay              : 100 ;"
                                      "default            : per 8 item(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"per \" ;"
                                      "suffix             : \" item(s)\" ;"
                                    //"minValue           : 0 ;"
                                    //"maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Float attributes",       "toolTip            : \"It is a Float\" ;"
                                      "delay              : 100 ;"
                                      "default            : I have 9.877 apple(s) ;"
                                      "wrapping           : true ;"
                                      "accelerated        : false ;"
                                      "prefix             : \"I have \" ;"
                                      "suffix             : \" apple(s)\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 30.73 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.1 ;"
           )

Q_CLASSINFO("Double attributes",      "toolTip            : \"It is a Double\" ;"
                                      "delay              : 100 ;"
                                      "default            : There is no 1.23457 human(s) ;"
                                      "wrapping           : false ;"
                                      "accelerated        : true ;"
                                      "prefix             : \"There is no \" ;"
                                      "suffix             : \" human(s)\" ;"
                                      "minValue           : 0.05 ;"
                                      "maxValue           : 54.34 ;"
                                      "decimals           : 5 ;"
                                      "step               : 0.03 ;"
           )

Q_CLASSINFO("Char attributes",        "toolTip            : \"It is a Char\" ;"
                                      "delay              : 100 ;"
                                      "default            : T ;"
                                      "inputMask          : >A! ;"
                                      "echoMode           : Normal ;"
                                      "placeholderText    : \"Insert capital\" ;"
           )

Q_CLASSINFO("Map attributes",         "toolTip            : \"It is a Map\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(\"03.12.87\", 5), (\"13.04.95\", 2), (\"27.09.12\", 4)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" book(s)\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("List attributes",        "toolTip            : \"It is a List\" ;"
                                      "delay              : 100 ;"
                                      "default            : [8 PC(s), 2 PC(s), 6 PC(s)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" PC(s)\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 10 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("StringList attributes",  "toolTip            : \"It is a StringList\" ;"
                                      "delay              : 100 ;"
                                      "default            : [\"Ann\", \"John\", \"Mary\"] ;"
                                      "minCount           : 1 ;"
                                      "maxCount           : 5 ;"

                                    //"inputMask          : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                      "maxLength          : 10 ;"
                                    //"echoMode           : PasswordEchoOnEdit ;"
                                      "placeholderText    : \"Insert name\" ;"
           )

Q_CLASSINFO("String attributes",      "toolTip            : \"It is a String\" ;"
                                      "delay              : 100 ;"
                                    //"default            : My_Password ;"
                                    //"inputMask          : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                      "maxLength          : 16 ;"
                                      "echoMode           : PasswordEchoOnEdit ;"
                                      "placeholderText    : \"Insert password\" ;"
           )

Q_CLASSINFO("ByteArray attributes",   "toolTip            : \"It is a ByteArray\" ;"
                                      "delay              : 100 ;"
                                    //"default            : ;"
                                      "alternateBaseColor : #FF0000 ;"
           )

Q_CLASSINFO("BitArray attributes",    "toolTip            : \"It is a BitArray\" ;"
                                      "delay              : 100 ;"
                                    //"default            : ;"
                                      "alternateBaseColor : #FF0000 ;"
           )

Q_CLASSINFO("Date attributes",        "toolTip            : \"It is a Date\" ;"
                                      "delay              : 100 ;"
                                    //"default            : 2012-12-19 ;"
                                      "minDate            : 01.01.2000 ;"
                                      "maxDate            : 31.12.2020 ;"
                                      "displayFormat      : yyyy-MM-dd ;"
                                      "calendarPopup      : true ;"
           )

Q_CLASSINFO("Time attributes",        "toolTip            : \"It is a Time\" ;"
                                      "delay              : 100 ;"
                                    //"default            : 20:32:30.861 ;"
                                      "minTime            : 12:34:56 ;"
                                      "maxTime            : 23:59:59 ;"
                                      "displayFormat      : HH:mm:ss.zzz ;"
           )

Q_CLASSINFO("DateTime attributes",    "toolTip            : \"It is a DateTime\" ;"
                                      "delay              : 100 ;"
                                    //"default            : 2012-12-19 20:32:30.861 ;"
                                      "minDate            : 01.01.2000 ;"
                                      "maxDate            : 31.12.2020 ;"
                                      "minTime            : 12:34:56 ;"
                                      "maxTime            : 23:59:59 ;"
                                      "displayFormat      : yyyy-MM-dd HH:mm:ss.zzz ;"
                                      "calendarPopup      : true ;"
           )

Q_CLASSINFO("Url attributes",         "toolTip            : \"It is a Url\" ;"
                                      "delay              : 100 ;"
                                      "default            : http:/google.com ;"
                                    //"inputMask          : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                    //"maxLength          : 16 ;"
                                    //"echoMode           : Password ;"
                                      "placeholderText    : \"Insert url\" ;"
           )

Q_CLASSINFO("Locale attributes",      "toolTip            : \"It is a Locale\" ;"
                                      "delay              : 100 ;"
                                      "default            : Russian, RussianFederation ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"
           )

Q_CLASSINFO("Rect attributes",        "toolTip            : \"It is a Rect\" ;"
                                      "delay              : 100 ;"
                                      "default            : (10, 20, 800 x 600) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "step               : 10 ;"
           )

Q_CLASSINFO("RectF attributes",       "toolTip            : \"It is a RectF\" ;"
                                      "delay              : 100 ;"
                                      "default            : (20, 10, 640 x 480) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.1 ;"
           )

Q_CLASSINFO("Size attributes",        "toolTip            : \"It is a Size\" ;"
                                      "delay              : 100 ;"
                                      "default            : 32 x 32 ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "step               : 10 ;"
           )

Q_CLASSINFO("SizeF attributes",       "toolTip            : \"It is a SizeF\" ;"
                                      "delay              : 100 ;"
                                      "default            : 48 x 48 ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.1 ;"
           )

Q_CLASSINFO("Line attributes",        "toolTip            : \"It is a Line\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(10, 10), (600, 10)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "step               : 10 ;"
           )

Q_CLASSINFO("LineF attributes",       "toolTip            : \"It is a LineF\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(4, 4), (4, 300)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.1 ;"
           )

Q_CLASSINFO("Point attributes",       "toolTip            : \"It is a Point\" ;"
                                      "delay              : 100 ;"
                                      "default            : (320, 240) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "step               : 10 ;"
           )

Q_CLASSINFO("PointF attributes",      "toolTip            : \"It is a PointF\" ;"
                                      "delay              : 100 ;"
                                      "default            : (240, 320) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 2000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.1 ;"
           )

Q_CLASSINFO("RegExp attributes",      "toolTip            : \"It is a RegExp\" ;"
                                      "delay              : 100 ;"
                                      "default            : ^[a-z] ;"
                                    //"inputMask          : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                    //"maxLength          : 16 ;"
                                    //"echoMode           : Password ;"
                                      "placeholderText    : \"Insert RegExp\" ;"
           )

Q_CLASSINFO("Hash attributes",        "toolTip            : \"It is a Hash\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(\"World!\", 9), (\"From\", 7), (\"Russia\", 2), (\"Hello\", 6)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" ID\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 255 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("EasingCurve attributes", "toolTip            : \"It is a EasingCurve\" ;"
                                      "delay              : 100 ;"
                                      "default            : (InOutCubic, 1, 1.702, 0.3) ;"
                                      "allowSetType       : false ;"
                                      "preview            : false ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" `\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 100 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Font attributes",        "toolTip            : \"It is a Font\" ;"
                                      "delay              : 100 ;"
                                      "default            : (Times New Roman, 12, K, PreferDefault) ;"
                                      "allowModifySample  : true ;"

                                    //"inputMask          : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                    //"maxLength          : 16 ;"
                                    //"echoMode           : Password ;"
                                      "placeholderText    : \"Insert font family\" ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" pt\" ;"
                                      "minValue           : 9 ;"
                                      "maxValue           : 36 ;"
                                      "step               : 1 ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"
           )

Q_CLASSINFO("Pixmap attributes",      "toolTip            : \"It is a Pixmap\" ;"
                                      "delay              : 100 ;"
                                    //"default            : 64 x 64 ;"
                                      "color1             : #ABCDEF ;"
                                      "color28            : #FEDCBA ;"
                                      "allowOpen          : false ;"
                                      "allowResize        : false ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 5000 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Brush attributes",       "toolTip            : \"It is a Brush\" ;"
                                      "delay              : 100 ;"
                                      "default            : (RadialGradientPattern, (0, (255, 255, 255)), (1, (0, 0, 0))) ;"
                                    //"allowSetBrushStyle : false ;"
                                    //"allowGradient      : false ;"
                                    //"allowTransform     : false ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \"!\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Color attributes",       "toolTip            : \"It is a Color\" ;"
                                      "delay              : 100 ;"
                                      "default            : (128, 0, 255) ;"
                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"
           )

Q_CLASSINFO("Palette attributes",     "toolTip            : \"It is a Palette\" ;"
                                      "delay              : 100 ;"
                                    //"default            : [] ;"
                                      "allowFastColor     : false ;"
                                      "allowChangeDetails : true ;"
                                      "showDetails        : true ;"
                                      "preview            : true ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"
           )

Q_CLASSINFO("Icon attributes",        "toolTip            : \"It is a Icon\" ;"
                                      "delay              : 100 ;"
                                    //"default            : Icon ;"
                                      "tabOthers          : false ;"
                                      "tabNormalOFF       : true ;"

                                      "color1             : #ABCDEF ;"
                                      "color28            : #FEDCBA ;"
                                      "allowOpen          : true ;"
                                      "allowResize        : true ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 5000 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Image attributes",       "toolTip            : \"It is a Image\" ;"
                                      "delay              : 100 ;"
                                    //"default            : 64 x 64 ;"
                                      "color1             : #ABCDEF ;"
                                      "color28            : #FEDCBA ;"
                                      "allowOpen          : true ;"
                                      "allowResize        : false ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 5000 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Polygon attributes",     "toolTip            : \"It is a Polygon\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(10, 40), (30, 97), (43, 16)] ;"
                                      "minCount           : 1 ;"
                                      "maxCount           : 5 ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : -2000 ;"
                                      "maxValue           : 2000 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Region attributes",      "toolTip            : \"It is a Region\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(10, 30, 40 x 90)] ;"
                                      "minCount           : 1 ;"
                                      "maxCount           : 5 ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : -2000 ;"
                                      "maxValue           : 2000 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Bitmap attributes",      "toolTip            : \"It is a Bitmap\" ;"
                                      "delay              : 100 ;"
                                    //"default            : 64 x 64 ;"
                                      "allowOpen          : false ;"
                                      "allowResize        : true ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 5000 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("Cursor attributes",      "toolTip            : \"It is a Cursor\" ;"
                                      "delay              : 100 ;"
                                      "default            : PointingHandCursor ;"
                                      "allowBitmap        : false ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" px\" ;"
                                      "minValue           : -100 ;"
                                      "maxValue           : 100 ;"
                                      "step               : 1 ;"

                                      "color1             : #ABCDEF ;"
                                      "color28            : #FEDCBA ;"
                                      "allowOpen          : true ;"
                                      "allowResize        : false ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"
           )

Q_CLASSINFO("SizePolicy attributes",  "toolTip            : \"It is a SizePolicy\" ;"
                                      "delay              : 100 ;"
                                      "default            : (Minimum, Expanding, 0, 0) ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \"#\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 100 ;"
                                      "step               : 1 ;"
           )

Q_CLASSINFO("KeySequence attributes", "toolTip            : \"It is a KeySequence\" ;"
                                      "delay              : 100 ;"
                                      "default            : Ctrl+O ;"
                                      "rejectShortcuts    : Ctrl+S|Alt+X|A|B|C|D|E ;"
           )

Q_CLASSINFO("Pen attributes",         "toolTip            : \"It is a Pen\" ;"
                                      "delay              : 100 ;"
                                      "default            : (DotLine, SquareCap, BevelJoin, 2, (SolidPattern, (0, 0, 0))) ;"
                                      "allowSetStyle      : false ;"
                                      "allowSetCapStyle   : false ;"
                                      "allowSetJoinStyle  : false ;"

                                    //"allowSetBrushStyle : false ;"
                                    //"allowGradient      : false ;"
                                    //"allowTransform     : false ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                      "alphaEnabled       : false ;"
                                      "standardColor1     : #ABCDEF ;"
                                      "standardColor48    : #FEDCBA ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \"!\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("TextLength attributes",  "toolTip            : \"It is a TextLength\" ;"
                                      "delay              : 100 ;"
                                      "default            : (PercentageLength, 90) ;"
                                      "allowSetLengthType : false ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \" %\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 100 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("TextFormat attributes",  "toolTip            : \"It is a TextFormat\" ;"
                                      "delay              : 100 ;"
                                      "default            : TableFormat ;"
                                      "allowSetFormatType : true ;"

                                      "maxVisibleItems    : 5 ;"
                                      "editable           : false ;"
                                    //"values             : ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                      "suffix             : \"$\" ;"
                                      "minValue           : 0 ;"
                                      "maxValue           : 100 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"

                                    //"inputMask          : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                      "maxLength          : 16 ;"
                                    //"echoMode           : Password ;"
                                      "placeholderText    : \"Modify TextFormat\" ;"
           )

Q_CLASSINFO("Matrix attributes",      "toolTip            : \"It is a Matrix\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(6, 9), (12, 5), (7, 6)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Transform attributes",   "toolTip            : \"It is a Transform\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(1, 2, 3), (4, 5, 6), (7, 8, 9)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Matrix4x4 attributes",   "toolTip            : \"It is a Matrix4x4\" ;"
                                      "delay              : 100 ;"
                                      "default            : [(16, 15, 14, 13), (12, 11, 10, 9), (8, 7, 6, 5), (4, 3, 2, 1)] ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Vector2D attributes",    "toolTip            : \"It is a Vector2D\" ;"
                                      "delay              : 100 ;"
                                      "default            : (6, 7) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Vector3D attributes",    "toolTip            : \"It is a Vector3D\" ;"
                                      "delay              : 100 ;"
                                      "default            : (1, 5, 8) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Vector4D attributes",    "toolTip            : \"It is a Vector4D\" ;"
                                      "delay              : 100 ;"
                                      "default            : (4, 3, 9, 6) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Quaternion attributes",  "toolTip            : \"It is a Quaternion\" ;"
                                      "delay              : 100 ;"
                                      "default            : (1, 7, 6, 5) ;"

                                    //"wrapping           : false ;"
                                    //"accelerated        : false ;"
                                    //"prefix             : \"\" ;"
                                    //"suffix             : \" `\" ;"
                                      "minValue           : -1000 ;"
                                      "maxValue           : 1000 ;"
                                      "decimals           : 3 ;"
                                      "step               : 0.001 ;"
           )

Q_CLASSINFO("Void attributes",        "toolTip            : \"It is a Void\" ;"
                                      "delay              : 100 ;"
                                    //"default            : ;"
           )

Q_CLASSINFO("Object attributes",      "toolTip            : \"It is a Object\" ;"
                                      "delay              : 100 ;"
                                    //"default            : ;"
           )
