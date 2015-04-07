//
//  SQLConnection.h
//  SQLConnect
//
//  Created by Nick Griffith on 3/16/14.
//  Copyright (c) 2014 nhg. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SQLConnectionDelegate.h"
#import "SQLSettings.h"

@interface SQLConnection : NSObject

#pragma mark Properties
/**
 *  Indicates whether or not the database is currently connected
 */
@property (nonatomic,assign,readonly) BOOL connected;

/**
 *  The database server to use.  Supports server, server:port, or server\instance (be sure to escape the backslash)
 */
@property (nonatomic,strong) NSString *server;

/**
 *  The database username
 */
@property (nonatomic,strong) NSString *username;

/**
 *  The database password
 */
@property (nonatomic,strong) NSString *password;

/**
 *  The database name to use
 */
@property (nonatomic,strong) NSString *database;

/**
 *  Delegate to handle callbacks
 */
@property (nonatomic,weak) NSObject<SQLConnectionDelegate> *delegate;

/**
 *  The queue to execute database operations on.  A default queue name is used, but can be overridden.
 */
@property (nonatomic,strong) NSOperationQueue *workerQueue;

/**
 *  The queue for delegate callbacks.  Uses current queue by default, but can be overridden.
 */
@property (nonatomic,strong) NSOperationQueue *callbackQueue;

/**
 *  The character set to use for converting the UCS-2 server results. Default is UTF-8. Can be overridden to any charset supported by the iconv library. 
 *  To list all supported iconv character sets, open a Terminal window and enter:
 *  $ iconv --list
 */
@property (nonatomic,strong) NSString *charset;

/**
 *  Login timeout, in seconds. Default is 5.  Override before calling connect
 */
@property (nonatomic,assign) int loginTimeout;

/**
 *  Query timeout, in seconds. Default is 5. Override before calling executeQuery:
 */
@property (nonatomic,assign) int executeTimeout;

/*
 *  Tag for the object.  Not used internally at all.  Only used for the user to distinguish which connection is calling the delegate method if wanted.
 */
@property (nonatomic,assign) NSInteger tag;

/*
 *  User data for object.  Not user internally at all.  Can hold any information you want to retrieve in delegate methods.
 */
@property (nonatomic,strong) NSDictionary *userData;

#pragma mark Initializer methods

- (id)init __attribute__((unavailable("Must initialize with a delegate")));

/**
 *  Returns a SQLConnection instance using the defaults defined in the SQLSettings defaultSettings object
 *
 *  @param delegate Required. An object conforming to the SQLConnectionDelegate protocol for receiving callback messages.
 *
 *  @return SQLConnection object using the SQLSettings defaultSettings
 */
+ (instancetype)sqlConnectionWithDelegate:(NSObject<SQLConnectionDelegate>*)delegate;

/**
 *  Returns a SQLConnection instance
 *
 *  @param server   Required. The database server to use.  Supports server, server:port, or server\instance (be sure to escape the backslash)
 *  @param username Required. The database username.
 *  @param password Required. The database password.
 *  @param database Required. The database name.
 *  @param delegate Required. An object conforming to the SQLConnectionDelegate protocol for receiving callback messages.
 *
 *  @return SQLConnection object
 */
- (id)initWithServer:(NSString*)server
            username:(NSString*)username
            password:(NSString*)password
            database:(NSString*)database
            delegate:(id<SQLConnectionDelegate>)delegate;

/**
 *  Returns a SQLConnection instance
 *
 *  @param server   Required. The database server to use.  Supports server, server:port, or server\instance (be sure to escape the backslash)
 *  @param username Required. The database username.
 *  @param password Required. The database password.
 *  @param database Required. The database name.
 *  @param delegate Required. An object conforming to the SQLConnectionDelegate protocol for receiving callback messages.
 *
 *  @return SQLConnection object
 */
+ (instancetype)sqlConnectionWithServer:(NSString*)server
                               username:(NSString*)username
                               password:(NSString*)password
                               database:(NSString*)database
                               delegate:(NSObject<SQLConnectionDelegate>*)delegate;

/**
 *  Returns a SQLConnection instance
 *
 *  @param settings Required. The settings to use for connecting to the database.
 *  @param delegate Required. An object conforming to the SQLConnectionDelegate protocol for receiving callback messages.
 *
 *  @return SQLConnection object
 */
- (id)initWithSettings:(SQLSettings*)settings delegate:(NSObject<SQLConnectionDelegate>*)delegate;

/**
 *  Returns a SQLConnection instance
 *
 *  @param settings Required. The settings to use for connecting to the database.
 *  @param delegate Required. An object conforming to the SQLConnectionDelegate protocol for receiving callback messages.
 *
 *  @return SQLConnection object
 */
+ (instancetype)sqlConnectionWithSettings:(SQLSettings*)settings delegate:(NSObject<SQLConnectionDelegate>*)delegate;

#pragma mark Working methods

/**
 *  Connects to the SQL database using the current connection settings.
 */
- (void)connect;

/*
 *  An optional alternative to connect.  This method frees the connection info immediately after the connection attempt so it is not kept in memory.
 *
 *  @param server   Required. The database server to use.  Supports server, server:port, or server\instance (be sure to escape the backslash)
 *  @param username Required. The database username.
 *  @param password Required. The database password.
 *  @param database Required. The database name.
 *  @param charset  Optional. The charset to use.  Will default to preset charset if nil is passed.
 */
- (void)connectToServer:(NSString *)server withUsername:(NSString *)username password:(NSString *)password usingDatabase:(NSString *)database charset:(NSString *)charset;

/**
 *  Executes the provided SQL statement.  Results are handled via the delegate methods.
 */
- (void)execute:(NSString*)statement;

/**
 *  Disconnects from database server
 */
- (void)disconnect;


@end