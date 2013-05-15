/* This file is part of meegoimengine *
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 * Contact: Nokia Corporation (directui@nokia.com)
 *
 * If you have questions regarding the use of this file, please contact
 * Nokia at directui@nokia.com.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file LICENSE.LGPL included in the packaging
 * of this file.
 */

#ifndef MIMENGINEWORDSINTERFACE_H
#define MIMENGINEWORDSINTERFACE_H

#include "mimenginetypes.h"
#include <QString>
#include <QtPlugin>

class QPoint;
class QStringList;

/*!
  \class MImEngineWordsInterface

  \brief Abstract driver class for adding new error correction/prediction
  engines plugins.

  Implementing a new engine driver means to subclass and implement the virtual methods.
 */
class MImEngineWordsInterface
{
public:
    /*!
     * Initialization
     *\param parent point of QObject*
     *\return bool
     */
    virtual bool init() = 0;

    /*!
     * Adds a new word to dictionary
     *\param word, reference of const QString
     *\param MImEngine::DictionaryType to which type of dictionary the word should be added
     *\return bool true if the word is successfully added
     */
    virtual bool addDictionaryWord(const QString &word,
                                   MImEngine::DictionaryType) = 0;

    /*!
     * Removes a word from dictionary
     *\param word, reference of const QString
     *\param MImEngine::DictionaryType from which type of dictionary the word should be removed
     *\return bool true if the word is successfully removed
     */
    virtual bool removeDictionaryWord(const QString &word,
                                      MImEngine::DictionaryType) = 0;

    /*!
     * Disables dictionary
     *\param MImEngine::DictionaryType dictionary type which shall be disabled
     *\return bool true if the dictionary is successfully disabled
     */
    virtual bool disableDictionary(MImEngine::DictionaryType) = 0;

    /*!
     * Enables dictionary
     *\param MImEngine::DictionaryType dictionary type which shall be enabled
     *\return bool true if the dictionary is successfully enabled
     */
    virtual bool enableDictionary(MImEngine::DictionaryType) = 0;

    /*!
     * Removes dictionary from disk
     *\param MImEngine::DictionaryType dictionary type which shall be removed
     *\return bool true if dictionary is successfully removed
     */
    virtual bool removeDictionary(MImEngine::DictionaryType) = 0;

    /*!
     * Appends one character to engine buffer
     * \param s, reference of const QString
     */
    virtual void appendString(const QString &s) = 0;

    /*!
     * Appends string to engine buffer
     * \param c, reference of const QChar
     */
    virtual void appendCharacter(const QChar &c) = 0;

    /*!
     * Tap to keyboard
     * \param position, position of the tap in the keyboard layout
     * \param shift, indicates whether the shift is on or not
     * \param symbol, the preferred symbol
     */
    virtual void tapKeyboard(const QPoint &position, bool shift, QChar symbol) = 0;

    /*!
     * Reselects a previously accepted word. Called when user highlights a previously accepted
     * word to recreate the candidate list with the original input sequence and key values.
     * \param s, word to reselect
     */
    virtual void reselectString(const QString &s) = 0;

    /*!
     * Sets context information to the engine. \n
     * Context information is needed for better completion or for next word completion. 
     * The context information is usually a part of committed texts which should be passed 
     * to the engine before getting the completed/predicted word/character sequence from 
     * the engine.
     * \param s, the text block used as context information.
     * \param cursor, the cursor position in the text block.
     */
    virtual void setContext(const QString &s, int cursor) = 0;

    /*!
     * Disables word prediction feature
     */
    virtual void disablePrediction() = 0;

    /*!
     * Enables word prediction feature
     *\param  N/A
     *\return N/A
     */
    virtual void enablePrediction() = 0;

    /*!
     * Gets the current status of word prediction
     *\param  N/A
     *\return bool, true if word prediction is enabled
     */
    virtual bool predictionEnabled() = 0;

    /*!
     * Disables word completion feature
     */
    virtual void disableCompletion() = 0;

    /*!
     * Enables word completion feature.
     */
    virtual void enableCompletion() = 0;

    /*!
     * Gets the current status of word completion
     *\return bool, true if word completion is enabled
     */
    virtual bool completionEnabled() = 0;

    /*!
     * Disables auto correction feature
     * Notes: For Chinese input methods, this feature may stand for "Fuzzy matching".
     */
    virtual void disableCorrection() = 0;

    /*!
     * Enables auto correction feature
     * Notes: For Chinese input methods, this feature may stand for "Fuzzy matching".
     */
    virtual void enableCorrection() = 0;

    /*!
     * Gets the current status of auto correction
     * Notes: For Chinese input methods, this feature may stand for "Fuzzy matching".
     *\return bool, true if auto correction is enabled
     */
    virtual bool correctionEnabled() = 0;

    /*!
     * Clears engine input buffer. Note: clearEngineBuffer will not save the input word and its frequency.
     * \sa saveAndClearEngineBuffer(), appendString(), appendCharacter()
     */
    virtual void clearEngineBuffer() = 0;

    /*!
     * Saves the input word in engine buffer, and then clears the engine input buffer.
     * Engine will store the input word to user dictionary (if new word), and store its used frequency.
     * \sa appendString(), appendCharacter()
     */
    virtual void saveAndClearEngineBuffer() = 0;

    /*!
     * Gets the candidates given by the engine. \n
     * Notes:
     * -# By default, this method returns a candidate list which contains all candidates as much as 
     * the number which is specified by "setMaximumCandidates()".
     * -# If you want to specify the start index and the number of the candidates that you want, please
     * pass your arguments to this method.
     * -# The index of whole candidates starts from "0". And if your specified index or number exceeds 
     * the actual range of candidates, an empty candidate list will be returned.
     *
     *\param uStartIndex, the start index of the whole candidate set. And the index starts from "0".
     *\param uNum, the number of required candidates. If its value is "0", the default "Maximum" of 
     * candidates will be returned.
     *\return QStringList, the list of words given by the engine
     */
    virtual QStringList candidates(unsigned int uStartIndex = 0, unsigned int uNum = 0) = 0;

    /*!
     * Gets the number of all available candidates currently.
     * \return int, the number of all available candidates or -1 if failure occurs.
     */
    virtual int totalCandidates() = 0;

    /*!
     * Gets matched length of the chosen candidate for current input sequence. \n
     * Notes:
     * According to the input character sequence, "candidates()" can return a list and the user can choose
     * one candidate from it and notify the result to the engine by invoking "setSuggestedCandidateIndex()" 
     * or "setContext()" method. The chosen candidate might not match the whole input sequence and might 
     * match only part of the input sequence. So this method will tell the matched length of the chosen 
     * candidate for current input sequence.
     *\return int, the matched length of the chosen candidate for current input sequence.
     */
    virtual int matchedLength() = 0;

    /*!
     * Gets recognized syllables from current input string.
     * Notes:
     * In some input methods, the input string can be divided into several syllables according to
     * the most possible candidates. So in this case the input method engine shall list the recognized
     * syllables in order to give the user some prompts.
     * \return QStringList, the list of recognized syllables.
     */
    virtual QStringList matchedSyllables() = 0;

    /*!
     * Returns the index in the candidate list suggested by the engine as the most appropriate candidate.
     * Call this after calling candidates(). Useful when doing error correction.
     *\return the index of suggested candidate
     *\sa candidates()
     */
    virtual int suggestedCandidateIndex() = 0;

    /*!
     * Sets the index of the suggested candidate in the candidates' list, when user select one word from the
     * candidates' list, this API should be called, to info engine which one is the user preferred,
     * then the engine can store the relative information( new word, used frequency, etc.).
     *\param index, the index which is use selected
     *\return indicate whether set seccessfully.
     */
    virtual bool setSuggestedCandidateIndex(int index) = 0;

    /*!
     * Sets exact word position in candidate list. Call this to tell engine to position the exact word candidate in the list.
     * The exact word  can appear in first or last position
     * of the candidate list and can also can be deleted from the candidate list.
     * \param setting, indicates whether the exact word in the cadidate list.
     *
     * \sa MImEngine::ExactInListType.
     */
    virtual void setExactWordPositionInList(MImEngine::ExactInListType setting) = 0;

    /*!
     * Returns the source dictionary where the candidate comes from.
     *
     * \param index indicates the index of candidate in the candidates() list.
     * \sa candidates().
     */
    virtual MImEngine::DictionaryType candidateSource(int index) = 0;

    /*!
     * Gets current language
     *\param  N/A
     *\return QString, current language
     */
    virtual QString language() = 0;


    /*!
     * Sets language with the indicated priority
     *\param  lang, reference of const QString. the language to be set
     *\param  MImEngine::LanguagePriority. the priority for the language
     *\return N/A
     */
    virtual bool setLanguage(const QString &lang,
                             MImEngine::LanguagePriority) = 0;

    /*!
     * DEPRECATED !!! Use setKeyboardLayoutKeys instead!
     */
    bool setKeyboardLayout(const QString &) { return false; }

    /*!
     * DEPRECATED !!! Use keyboardLayoutKeys instead!
     */
    QString keyboardLayout()  { return QString(); }

    /*!
     * Loads new keyboard layout keys for the engine.
     * \param keys, list of keys in the keyboard layout
     * \return bool, status
     */
    virtual bool setKeyboardLayoutKeys(const QList<MImEngine::KeyboardLayoutKey> &keys) = 0;

    /*!
     * Gets current keyboard layout keys
     *\param  N/A
     *\return QList<MImEngine::KeyboardLayoutKey>, current keyboard layout keys
     */
    virtual QList<MImEngine::KeyboardLayoutKey> keyboardLayoutKeys() = 0;

    /*!
     * Exports the user dictionary into an xml file
     * \return bool status
     */
    virtual bool exportAsNokiaDictionary(const QString &fileName) = 0;

    /*!
      * Imports user dictionary from an xml file
      * \return bool status
      */
    virtual bool importNokiaUserDictionary(const QString &fileName) = 0;

    /*!
     * Gets name for current driver
     *\param  N/A
     *\return QString, current driver name
     */
    virtual QString driver() = 0;

    /*!
     * Sets the maximum number of errors could happen in a word.
     *\param int, the maximum number to be set
     *\return N/A
     * \sa setMaximumCandidates()
     */
    virtual void setMaximumErrors(int maxErrors) = 0;

    /*!
     * Gets the maximum number of errors that could happen in a word.
     *\param  N/A
     *\return int, the maximum allowed errors in a word. If the errors in a word is larger than this,
     * then engine maybe can not do proper correction.
     */
    virtual int maximumErrors() = 0;

    /*!
     * Sets the maximum number of candidates, including prediction and error correction
     * The maximum number can not be bigger than 10.
     *\param int, the maximum number to be set
     *\return N/A
     */
    virtual void setMaximumCandidates(int maxCandidates) = 0;

    /*!
     * Sets the maximum number for candidates, including prediction and error correction
     *\param  N/A
     *\return int, the allowed maximum candidates' count
     */
    virtual int maximumCandidates() = 0;

    /*!
     * Sets current input method engine's script by four-letter script code. \n
     * Notes: The ISO definition of four-letter script code is at 
     *        "http://www.unicode.org/iso15924/iso15924-codes.html". 
     *        The above definition should be followed here.
     *\param s, the text string of four-letter script code.
     *\return bool, true for success, otherwise false.
     */
    virtual bool setScript(const QString &s) = 0;

    /*! 
     * Gets four-letter script code of current input method engine.
     *\return QString, the four-letter script code of current input method engine.
     */
    virtual QString script() = 0;

    /*!
     * Gets error
     *\param  N/A
     *\return QString, error
     */
    virtual QString error() = 0;
};

Q_DECLARE_INTERFACE(MImEngineWordsInterface,
                    "com.nokia.Meego.MImEngineWordsInterface/0.1")


#endif // MIMENGINEWORDSINTERFACE_H

/*! \page
\section intro_sec Input Method Engine Words Interface

This interface provides typical word related functionalities, e.g. word prediction, word completion and error correction.

 */
