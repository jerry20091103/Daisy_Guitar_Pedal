#ifndef IR_FILTER_EFFECT_H
#define IR_FILTER_EFFECT_H

#include "effects.h"

class IR_filter_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;

private:
    daisysp::FIR<512, 1> fir;
    float mix;
    float ir_01[512] = {
    0.06755
    ,0.18365
    ,0.23449
    ,0.28241
    ,0.31623
    ,0.27538
    ,0.20813
    ,0.11946
    ,0.02559
    ,-0.05352
    ,-0.10248
    ,-0.11996
    ,-0.11160
    ,-0.09438
    ,-0.05473
    ,0.00911
    ,0.03863
    ,0.03703
    ,0.03696
    ,0.03456
    ,0.02088
    ,0.00822
    ,0.00837
    ,0.00849
    ,-0.00658
    ,-0.00994
    ,-0.01617
    ,-0.02614
    ,-0.02236
    ,-0.04742
    ,-0.06438
    ,-0.05677
    ,-0.05737
    ,-0.05320
    ,-0.02927
    ,-0.00432
    ,0.00496
    ,0.01528
    ,0.00560
    ,-0.02250
    ,-0.05356
    ,-0.07829
    ,-0.08579
    ,-0.08913
    ,-0.08357
    ,-0.06274
    ,-0.03053
    ,-0.01463
    ,-0.01833
    ,-0.01548
    ,-0.02527
    ,-0.04947
    ,-0.05565
    ,-0.05294
    ,-0.04960
    ,-0.03722
    ,-0.02055
    ,-0.00732
    ,0.00026
    ,0.00089
    ,-0.00488
    ,-0.00066
    ,-0.00220
    ,-0.01662
    ,-0.01179
    ,-0.00870
    ,-0.01489
    ,-0.01588
    ,-0.02273
    ,-0.02879
    ,-0.03351
    ,-0.03727
    ,-0.03590
    ,-0.02630
    ,-0.01379
    ,-0.00475
    ,0.00533
    ,0.00858
    ,-0.00277
    ,-0.01327
    ,-0.01756
    ,-0.02805
    ,-0.03536
    ,-0.03060
    ,-0.02813
    ,-0.02681
    ,-0.02000
    ,-0.01483
    ,0.00044
    ,0.01100
    ,0.01073
    ,0.01892
    ,0.01955
    ,0.00967
    ,0.00108
    ,-0.00481
    ,-0.01444
    ,-0.02710
    ,-0.03693
    ,-0.03850
    ,-0.03519
    ,-0.03172
    ,-0.02759
    ,-0.02522
    ,-0.02164
    ,-0.02277
    ,-0.02374
    ,-0.01800
    ,-0.01304
    ,-0.01015
    ,-0.00295
    ,0.00344
    ,0.00433
    ,0.00505
    ,0.00349
    ,0.00070
    ,-0.00547
    ,-0.01307
    ,-0.01666
    ,-0.01850
    ,-0.01914
    ,-0.01704
    ,-0.01370
    ,-0.01077
    ,-0.00949
    ,-0.00949
    ,-0.00714
    ,-0.00791
    ,-0.00971
    ,-0.00822
    ,-0.00729
    ,-0.00653
    ,-0.00534
    ,-0.00521
    ,-0.00557
    ,-0.00673
    ,-0.01196
    ,-0.01599
    ,-0.02024
    ,-0.02575
    ,-0.02822
    ,-0.02802
    ,-0.02513
    ,-0.02160
    ,-0.01590
    ,-0.00911
    ,-0.00438
    ,-0.00286
    ,-0.00195
    ,-0.00153
    ,-0.00238
    ,-0.00212
    ,-0.00271
    ,-0.00363
    ,-0.00375
    ,-0.00294
    ,-0.00179
    ,-0.00197
    ,-0.00144
    ,0.00141
    ,0.00141
    ,0.00057
    ,0.00277
    ,0.00196
    ,0.00109
    ,0.00156
    ,0.00100
    ,0.00011
    ,-0.00150
    ,-0.00187
    ,-0.00044
    ,0.00252
    ,0.00623
    ,0.00950
    ,0.01111
    ,0.01262
    ,0.01240
    ,0.01016
    ,0.00802
    ,0.00562
    ,0.00499
    ,0.00557
    ,0.00630
    ,0.00813
    ,0.01075
    ,0.01293
    ,0.01543
    ,0.01690
    ,0.01656
    ,0.01657
    ,0.01615
    ,0.01456
    ,0.01258
    ,0.01113
    ,0.01008
    ,0.00807
    ,0.00520
    ,0.00349
    ,0.00240
    ,0.00109
    ,0.00054
    ,0.00111
    ,0.00295
    ,0.00518
    ,0.00707
    ,0.00855
    ,0.00908
    ,0.00846
    ,0.00793
    ,0.00761
    ,0.00715
    ,0.00687
    ,0.00596
    ,0.00511
    ,0.00427
    ,0.00250
    ,0.00087
    ,-0.00013
    ,-0.00055
    ,-0.00051
    ,-0.00077
    ,-0.00063
    ,0.00098
    ,0.00296
    ,0.00532
    ,0.00758
    ,0.00866
    ,0.00959
    ,0.01070
    ,0.01218
    ,0.01397
    ,0.01563
    ,0.01732
    ,0.01875
    ,0.01897
    ,0.01838
    ,0.01726
    ,0.01557
    ,0.01435
    ,0.01442
    ,0.01619
    ,0.01887
    ,0.02174
    ,0.02448
    ,0.02614
    ,0.02542
    ,0.02306
    ,0.02011
    ,0.01675
    ,0.01344
    ,0.01045
    ,0.00865
    ,0.00745
    ,0.00619
    ,0.00544
    ,0.00538
    ,0.00604
    ,0.00727
    ,0.00853
    ,0.01022
    ,0.01201
    ,0.01185
    ,0.01116
    ,0.01113
    ,0.01081
    ,0.01045
    ,0.01045
    ,0.01101
    ,0.01178
    ,0.01233
    ,0.01285
    ,0.01371
    ,0.01389
    ,0.01337
    ,0.01223
    ,0.01059
    ,0.00948
    ,0.00868
    ,0.00843
    ,0.00858
    ,0.00849
    ,0.00841
    ,0.00897
    ,0.00969
    ,0.01078
    ,0.01186
    ,0.01214
    ,0.01319
    ,0.01417
    ,0.01443
    ,0.01470
    ,0.01474
    ,0.01422
    ,0.01303
    ,0.01194
    ,0.01088
    ,0.00958
    ,0.00847
    ,0.00741
    ,0.00652
    ,0.00624
    ,0.00620
    ,0.00655
    ,0.00743
    ,0.00829
    ,0.00913
    ,0.00990
    ,0.01001
    ,0.00993
    ,0.00993
    ,0.00966
    ,0.01013
    ,0.01088
    ,0.01136
    ,0.01196
    ,0.01252
    ,0.01311
    ,0.01372
    ,0.01441
    ,0.01556
    ,0.01702
    ,0.01762
    ,0.01710
    ,0.01584
    ,0.01414
    ,0.01193
    ,0.00911
    ,0.00608
    ,0.00301
    ,0.00033
    ,-0.00132
    ,-0.00200
    ,-0.00239
    ,-0.00272
    ,-0.00355
    ,-0.00489
    ,-0.00614
    ,-0.00727
    ,-0.00745
    ,-0.00678
    ,-0.00588
    ,-0.00456
    ,-0.00299
    ,-0.00125
    ,0.00075
    ,0.00224
    ,0.00288
    ,0.00232
    ,0.00037
    ,-0.00168
    ,-0.00370
    ,-0.00513
    ,-0.00495
    ,-0.00323
    ,-0.00005
    ,0.00388
    ,0.00716
    ,0.00957
    ,0.01106
    ,0.01093
    ,0.01053
    ,0.01018
    ,0.00966
    ,0.00964
    ,0.01011
    ,0.01091
    ,0.01130
    ,0.01101
    ,0.01016
    ,0.00897
    ,0.00742
    ,0.00546
    ,0.00375
    ,0.00293
    ,0.00310
    ,0.00402
    ,0.00515
    ,0.00618
    ,0.00680
    ,0.00645
    ,0.00509
    ,0.00254
    ,-0.00143
    ,-0.00536
    ,-0.00832
    ,-0.01080
    ,-0.01190
    ,-0.01143
    ,-0.01006
    ,-0.00822
    ,-0.00668
    ,-0.00582
    ,-0.00546
    ,-0.00567
    ,-0.00682
    ,-0.00831
    ,-0.00959
    ,-0.01130
    ,-0.01324
    ,-0.01390
    ,-0.01321
    ,-0.01184
    ,-0.00991
    ,-0.00808
    ,-0.00729
    ,-0.00729
    ,-0.00762
    ,-0.00888
    ,-0.01020
    ,-0.01106
    ,-0.01190
    ,-0.01157
    ,-0.01014
    ,-0.00856
    ,-0.00697
    ,-0.00539
    ,-0.00399
    ,-0.00263
    ,-0.00111
    ,0.00023
    ,0.00161
    ,0.00281
    ,0.00351
    ,0.00369
    ,0.00271
    ,0.00090
    ,-0.00076
    ,-0.00209
    ,-0.00340
    ,-0.00441
    ,-0.00465
    ,-0.00439
    ,-0.00366
    ,-0.00234
    ,-0.00022
    ,0.00207
    ,0.00333
    ,0.00393
    ,0.00433
    ,0.00407
    ,0.00300
    ,0.00171
    ,0.00028
    ,-0.00148
    ,-0.00296
    ,-0.00418
    ,-0.00513
    ,-0.00546
    ,-0.00511
    ,-0.00439
    ,-0.00405
    ,-0.00434
    ,-0.00518
    ,-0.00640
    ,-0.00782
    ,-0.00933
    ,-0.01086
    ,-0.01269
    ,-0.01464
    ,-0.01568
    ,-0.01542
    ,-0.01434
    ,-0.01288
    ,-0.01119
    ,-0.00944
    ,-0.00819
    ,-0.00766
    ,-0.00778
    ,-0.00829
    ,-0.00871
    ,-0.00923
    ,-0.00972
    ,-0.00985
    ,-0.00983
    ,-0.00951
    ,-0.00888
    ,-0.00817
    ,-0.00767
    ,-0.00763
    ,-0.00779
    ,-0.00789
    ,-0.00807
    ,-0.00768
    ,-0.00672
    ,-0.00607
    ,-0.00544
    ,-0.00484
    ,-0.00457
    ,-0.00504
    ,-0.00623
    ,-0.00741
    ,-0.00757
    ,-0.00639
    ,-0.00497
    ,-0.00355
    ,-0.00239
    ,-0.00266
    ,-0.00455
    ,-0.00718
    ,-0.00947
    ,-0.01091
    ,-0.01105
    ,-0.00951
    ,-0.00713
    ,-0.00515
    ,-0.00365
    ,-0.00283
    ,-0.00335
    ,-0.00435
    ,-0.00545
    ,-0.00685
    ,-0.00804

    };
};

#endif