
//
//  DrawAddOnViewController.m
//  DrawAddOn
//
//  Created by Sandeep Reddy Dega on 27/05/11.
//  Copyright 2011 Nunc Systems. All rights reserved.
//

#import "DrawAddOnViewController.h"
//#import<CoreGraphics/CoreGraphics.h>
#import <QuartzCore/QuartzCore.h>


@implementation DrawAddOnViewController
@synthesize imageNames;
@synthesize drawedScrollview,savedImageView;
@synthesize pageIndex;
@synthesize  mainView;
@synthesize editbutton;
@synthesize selectedThumbArt;
@synthesize delegate;

- (void)dealloc
{
    self.imageNames = nil;
    self.drawedScrollview = nil;
    self.savedImageView = nil;
    self.editbutton = nil;
    self.mainView = nil;
    
    self.selectedThumbArt = nil;
    self.delegate = nil;
    
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
}

#pragma mark -
-(void)thumbArtWorkSelected:(DrawedImage*)inThumbArtView;{
    if(self.selectedThumbArt != inThumbArtView){
        [self.selectedThumbArt.layer setCornerRadius:0.0];
        [self.selectedThumbArt.layer setBorderColor:[[UIColor clearColor] CGColor]];
        
        self.selectedThumbArt = inThumbArtView;
        [self.selectedThumbArt.layer setCornerRadius:10.0];
        [self.selectedThumbArt.layer setBorderColor:[[UIColor grayColor] CGColor]];
        
        if(self.selectedThumbArt.tag >= 0 && self.selectedThumbArt.tag < [self.imageNames count]){
            NSString *fileName = [self.imageNames objectAtIndex:self.selectedThumbArt.tag];
            [self setArtWorkWithFileName:fileName];
        }
    }
}

-(void)setArtWorkWithFileName:(NSString*)inFileName;{
    if(inFileName && [[NSFileManager defaultManager] fileExistsAtPath:inFileName]){
        self.savedImageView.image=[UIImage imageWithContentsOfFile:inFileName];
    }
}

#pragma mark -
-(IBAction)share:(id)sender;{
    if(![MFMailComposeViewController canSendMail]){
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Please check the email settings" message:nil delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        [alert release];
        return;
    }
    MFMailComposeViewController *_controller = [[MFMailComposeViewController alloc] init];  
    _controller.mailComposeDelegate = self;
    
    UIView *src = self.savedImageView;
    
    UIGraphicsBeginImageContext(src.bounds.size);
    [src.layer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *resultingImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    [src release];
    
    NSData *pdfData = UIImagePNGRepresentation(resultingImage);
    
    [_controller setSubject:@"Here is a drawing !"];
    [_controller setMessageBody:@" I have made this drawing for you with 'Design App' for iPad. For more information please visit www.icrglabs.com" isHTML:YES];
    
    [_controller addAttachmentData:pdfData mimeType:@"application/png" fileName:@"MyArt.png"];
    [self presentModalViewController:_controller animated:YES];
    [_controller release];
}

-(IBAction)removeSavedImageView:(id)sender{
    [self.view removeFromSuperview];
}

-(IBAction)editDrawing:(id)sender{
    NSString *fileName = nil;
    if(self.selectedThumbArt.tag >= 0 && self.selectedThumbArt.tag < [self.imageNames count]){
        fileName = [self.imageNames objectAtIndex:self.selectedThumbArt.tag];
        //NSLog(@"selected tag for editing is %@",fileName);
        // fileName = [NSString stringWithFormat:@"%@_UI",fileName];
//        //NSLog(@"filename is %@",fileName);
//        
//        //NSLog(@"Test Out put is %@",[fileName lastPathComponent]);
//       
//        
//        //NSLog(@"testss is %@",[fileName substringFromIndex:[fileName length]-3]);
        
        
        if([self.delegate respondsToSelector:@selector(fileDidSelectForEditing:)]){
            [self.delegate fileDidSelectForEditing:fileName];
        }
    }
    [self.view removeFromSuperview];
}

#pragma mark - load scrollview -

-(void)showDrawedScrollView {
    int xOffset = 10;
    int index=0;
    
    NSString *ui = @"_UI";
    NSString *open = @".png";
    
    for(NSString *fileName in self.imageNames){ 
        
        if([ui isEqualToString:[NSString stringWithFormat:@"%@",[fileName substringFromIndex:[fileName length]-3]]])
        {
            //return;
        }
        else if([open isEqualToString:[NSString stringWithFormat:@"%@",[fileName substringFromIndex:[fileName length]-4]]])
        {
           // return;
        }
        else
        {
            DrawedImage *thumbArt=[[DrawedImage alloc] initWithFrame:CGRectMake(xOffset, 17, 200, 145) withImageName:fileName];
            thumbArt.userInteractionEnabled=YES;
            thumbArt.delegate=self;
            thumbArt.tag=[self.imageNames indexOfObject:fileName];
            UIButton *deleteBtn = [[UIButton buttonWithType:UIButtonTypeCustom] retain];
            deleteBtn.tag=[self.imageNames indexOfObject:fileName];
            deleteBtn.frame = CGRectMake(0, 0, 50, 50);
            [deleteBtn setBackgroundImage:[UIImage imageNamed:@"delete.png"] forState:UIControlStateNormal];
            [deleteBtn addTarget:self action:@selector(deletealertview:) forControlEvents:UIControlEventTouchUpInside];
            deleteBtn.hidden = YES;
            thumbArt.deleteButton = deleteBtn;
            [thumbArt addSubview:deleteBtn];
            
            [self.drawedScrollview addSubview:thumbArt];
            
            xOffset += 210;
            index++;
            self.drawedScrollview.contentSize=CGSizeMake(xOffset, 0);
            
            if(nil == self.selectedThumbArt){
                self.selectedThumbArt = thumbArt;
                [self setArtWorkWithFileName:fileName];
            }
            [thumbArt release];
        }
    }
    if([imageNames count]>0){
    }
    else
    {
        CGRect rect = CGRectMake((CGRectGetWidth(self.view.frame)-300)*0.5, (CGRectGetHeight(self.view.frame)-100)*0.5, 300, 100);
        UILabel *showNoImagesLabel=[[UILabel alloc] initWithFrame:rect];
        showNoImagesLabel.tag = 555;
        showNoImagesLabel.layer.cornerRadius = 6.0f;
        showNoImagesLabel.text=@"No Artwork Available";
        showNoImagesLabel.textColor=[UIColor whiteColor];
        showNoImagesLabel.textAlignment = UITextAlignmentCenter;
        showNoImagesLabel.backgroundColor=[UIColor orangeColor];
        showNoImagesLabel.font=[UIFont boldSystemFontOfSize:28];
        [self.view addSubview:showNoImagesLabel];
        [showNoImagesLabel release];
        
        self.drawedScrollview.hidden = YES;
    }
    
    UIButton *deleteBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    deleteBtn.frame = CGRectMake(xOffset, 50, 132, 79);
    deleteBtn.tag = 666;
    UIImage *buttonImage = [UIImage imageNamed:@"delete_1_bt.png"];
    [deleteBtn setBackgroundImage:buttonImage forState:UIControlStateNormal];
    [deleteBtn addTarget:self action:@selector(showDeleteIcon) forControlEvents:UIControlEventTouchUpInside];
    
    [self.drawedScrollview addSubview:deleteBtn];
    
    xOffset += 135; 
    CGFloat xPoint = 1030;
    if(xOffset > xPoint) xPoint = xOffset;
    
    self.drawedScrollview.contentSize=CGSizeMake(xPoint, 0);
    
}

-(void)removeLabel{
    UILabel *showNoImagesLabel= (UILabel*)[self.view viewWithTag:555];
    if(showNoImagesLabel){
        [showNoImagesLabel removeFromSuperview];
    }
}


-(void)showDeleteIcon{
    NSArray *subview=[drawedScrollview subviews];
    for(DrawedImage *image in subview){
        if([image isKindOfClass:[DrawedImage class]]){
            image.deleteButton.hidden = !image.deleteButton.hidden;
        }
    }
}

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex == [alertView cancelButtonIndex]){ 
        NSArray *deleteview=[drawedScrollview subviews];
        CGFloat xOrigin = 0;
        CGFloat xPoint = 0;
        for(DrawedImage *child in deleteview){
            if([child isKindOfClass:[DrawedImage class]])
            {
                if(child.tag == alertView.tag){
                    xOrigin = CGRectGetMinX(child.frame);
                    [child removeFromSuperview];
                }
            }
        }
        
        for(DrawedImage *child in deleteview){
            if([child isKindOfClass:[DrawedImage class]])
            {
                if(CGRectGetMinX(child.frame) > xOrigin){
                    CGRect rect = child.frame;
                    rect.origin.x -= 210;
                    child.frame = rect;
                }
            }
            else if(666 == child.tag){
                CGRect rect = child.frame;
                rect.origin.x -= 210;
                child.frame = rect;
                xPoint = CGRectGetMaxX(child.frame)+30;
            }
        }
        
        if(xPoint < 1030) xPoint = 1030;
        
        self.drawedScrollview.contentSize=CGSizeMake(xPoint, 0);
        
        if(alertView.tag >=0 && alertView.tag < [self.imageNames count]){
            NSString *fileNametoDelete=[self.imageNames objectAtIndex:alertView.tag];
            [[NSFileManager defaultManager] removeItemAtPath:fileNametoDelete error:NULL];
        }
    }
}

-(void)deletealertview:(UIButton *)sender{
    UIAlertView *myAlertView = [[UIAlertView alloc] initWithTitle:@"Do you want to delete this?" message:@"" delegate:self cancelButtonTitle:@"YES" otherButtonTitles:@"NO", nil];
    myAlertView.tag = sender.tag;
    myAlertView.frame = CGRectMake(0, 0, 260.0, 500.0); 
    
    CGAffineTransform myTransform = CGAffineTransformMakeTranslation(0.0, 10.0);
    [myAlertView setTransform:myTransform];
    [myAlertView show];
    [myAlertView release]; 
}


#pragma mark - View lifecycle

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{  
    [super viewDidLoad];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    basePath = [basePath stringByAppendingPathComponent:@"DrawApp"];
    BOOL isDir;
    
    NSFileManager *fileManager=[NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:basePath isDirectory:&isDir] && isDir) {
        
        NSArray *tempimageNames=    [fileManager contentsOfDirectoryAtPath:basePath error:nil];
        for(NSString *name in tempimageNames){
            if([name isEqualToString:@".DS_Store"]){
            }
            else {
                if(imageNames==nil){
                    imageNames=[[NSMutableArray alloc]init ];
                }
                NSString *nameWithPath=[basePath stringByAppendingString:[NSString stringWithFormat:@"/%@", name]];    
                [imageNames addObject:nameWithPath];
            }
        }
    }
    
    pageIndex=0;
    [self showDrawedScrollView];
    
}

- (void)viewDidUnload
{
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight) {
		return YES;
	}
	return NO;
}

#pragma mark -
- (void)mailComposeController:(MFMailComposeViewController*)controller  
		  didFinishWithResult:(MFMailComposeResult)result 
						error:(NSError*)error;
{
	if (result == MFMailComposeResultSent) {
		
		UIAlertView *_uialertView=[[UIAlertView alloc] initWithTitle:@"Email" message:@"Email sent successfully." delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
		[_uialertView show];
		[_uialertView release];
	}
	
	[self dismissModalViewControllerAnimated:YES];
}
@end


