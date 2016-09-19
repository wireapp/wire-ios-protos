// 
// Wire
// Copyright (C) 2016 Wire Swiss GmbH
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.
// 


@import UIKit;
@import zimages;

#import <ZMProtos/ZMProtos.h>

@class ZMIImageProperties;
@class ZMConversation;


@interface ZMImageAssetEncryptionKeys: NSObject

/// Key used for symmetric encryption of the asset
@property (nonatomic, copy, readonly, nonnull) NSData *otrKey;
/// HMAC key used to compute the digest
@property (nonatomic, copy, readonly, nullable) NSData *macKey;
/// HMAC digest
@property (nonatomic, copy, readonly, nullable) NSData *mac;
/// SHA-256 digest
@property (nonatomic, copy, readonly, nullable) NSData *sha256;
/// Wether it has a HMAC digest
@property (nonatomic, readonly) BOOL hasHMACDigest;
/// Wether it has a SHA256 digest
@property (nonatomic, readonly) BOOL hasSHA256Digest;


- (nonnull instancetype)initWithOtrKey:(nonnull NSData *)otrKey macKey:(nonnull NSData *)macKey mac:(nonnull NSData *)mac;
- (nonnull instancetype)initWithOtrKey:(nonnull NSData *)otrKey sha256:(nonnull NSData *)sha256;

@end


NS_ASSUME_NONNULL_BEGIN

@interface ZMGenericMessage (Utils)

+ (nonnull ZMGenericMessage *)messageWithBase64String:(nonnull NSString *)string;
+ (nonnull ZMGenericMessage *)knockWithNonce:(nonnull NSString *)nonce;
+ (nonnull ZMGenericMessage *)sessionResetWithNonce:(nonnull NSString *)nonce;
+ (nonnull ZMGenericMessage *)messageWithText:(nonnull NSString *)message nonce:(nonnull NSString *)nonce;
+ (nonnull ZMGenericMessage *)messageWithText:(nonnull NSString *)message linkPreview:(nonnull ZMLinkPreview *)linkPreview nonce:(nonnull NSString *)nonce;
+ (nonnull ZMGenericMessage *)messageWithImageData:(nonnull NSData *)imageData format:(ZMImageFormat)format nonce:(nonnull NSString *)nonce;
+ (nonnull ZMGenericMessage *)messageWithConfirmation:(nonnull NSString *)messageID type:(ZMConfirmationType)type nonce:(nonnull NSString *)nonce;

+ (nonnull ZMGenericMessage *)messageWithMediumImageProperties:(nullable ZMIImageProperties *)mediumProperties
                              processedImageProperties:(nullable ZMIImageProperties *)processedProperties
                                        encryptionKeys:(nullable ZMImageAssetEncryptionKeys *)encryptionKeys
                                                 nonce:(nonnull NSString *)nonce
                                                format:(ZMImageFormat)format;

+ (nonnull ZMGenericMessage *)messageWithLastRead:(nonnull NSDate *)timestamp
                     ofConversationWithID:(nonnull NSString *)conversationIDString
                                    nonce:(nonnull NSString *)nonce;

+ (nonnull ZMGenericMessage *)messageWithClearedTimestamp:(nonnull NSDate *)timestamp
                     ofConversationWithID:(nonnull NSString *)conversationIDString
                                    nonce:(nonnull NSString *)nonce;

+ (nonnull ZMGenericMessage *)messageWithHideMessage:(nonnull NSString *)messageID
                              inConversation:(nonnull NSString *)conversationID
                                       nonce:(nonnull NSString *)nonce;

+ (nonnull ZMGenericMessage *)messageWithDeleteMessage:(nonnull NSString *)messageID
                                         nonce:(nonnull NSString *)nonce;

+ (nonnull ZMGenericMessage *)messageWithEditMessage:(nonnull NSString *)messageID
                                     newText:(nonnull NSString *)newText
                                       nonce:(nonnull NSString *)nonce;

+ (nonnull ZMGenericMessage *)messageWithEditMessage:(nonnull NSString *)messageID
                                     newText:(nonnull NSString *)newText
                                 linkPreview:(nonnull ZMLinkPreview *)linkPreview
                                       nonce:(nonnull NSString *)nonce;


+ (nonnull ZMGenericMessage *)messageWithEmojiString:(nonnull NSString *)emojiString
                                   messageID:(nonnull NSString *)messageID
                                       nonce:(nonnull NSString *)nonce;
- (BOOL)knownMessage;

@end

NS_ASSUME_NONNULL_END


@interface ZMImageAsset (Utils)

- (ZMImageFormat)imageFormat;

@end


